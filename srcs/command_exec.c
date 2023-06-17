/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:11:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/18 16:35:45 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "ft_signal.h"
#include "tokenize.h"
#include "libft.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define WRITE_FD 1
#define READ_FD 0

void *free_string_array(char **string_array)
{
	size_t i;

	i = 0;
	while (string_array[i] != NULL)
	{
		free(string_array[i]);
		i++;
	}
	free(string_array);
	return NULL;
}


size_t get_args_list_size(t_command *command)
{
	size_t size;
	
	t_args_list *args_list;
	args_list = command->args_list;
	size = 0;
	while (args_list != NULL)
	{
		args_list = args_list->next;
		size++;
	}
	return size;
}

char **make_args(t_command *command)
{
	size_t args_size;
	char **args_array;
	t_args_list *args_list;
	
	args_size = get_args_list_size(command) + 1;
	args_array = calloc(args_size + 1, sizeof(char *));
	if (args_array == NULL)
		return NULL;
	size_t i;
	args_array[0] = strdup(command->command_name);
	if (args_array[0] == NULL)
		return free_string_array(args_array);
	i = 1;
	args_list = command->args_list;
	while (args_list != NULL)
	{
		args_array[i] = strdup(args_list->string);
		if (args_array[i] == NULL)
			return free_string_array(args_array);
		i++;
		args_list = args_list->next;
	}
	return (args_array);
	
	// char **args = malloc(sizeof(char *) * 3);
	// args[0] = strdup("echo");
	// args[1] = strdup("hoge");
	// args[2] = NULL;
	// (void)command;
	// return args;
	
}


char *make_path(const char *path, const char *command)
{
	char *slashed;
	char *joined;
	
	if (path == NULL || command == NULL)
		return (NULL);
	slashed = ft_strjoin(path, "/");
	if (slashed == NULL)
		return (NULL);
	joined = ft_strjoin(slashed, command);
	free(slashed);
	return (joined);
}

char *find_path(t_command *command, t_env_manager *env_manager)
{
	// 絶対パスかのチェック
	if (access(command->command_name, F_OK) == 0)
		return strdup(command->command_name);
	t_env *path_env;

	size_t i;
	char *absolute_path;
	char **paths;
	path_env = find_env(env_manager, "PATH");
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		absolute_path = make_path(paths[i], command->command_name);
		if (absolute_path == NULL)
			return (free_string_array(paths));
		if (access(absolute_path, F_OK) == 0)
		{
			free_string_array(paths);
			return (absolute_path);
		}
		free(absolute_path);
		i++;
	}
	free_string_array(paths);
	return NULL;
}

int ft_exec(t_command *command, t_env_manager *env_manager)
{
	char	*command_path;
	command_path = find_path(command, env_manager);
	if (command_path == NULL)
	{
		write(STDERR_FILENO, "command not found\n", 18);;
		return (-1);
	}
	// TODO: envの$?に入れる　
	// fprintf(stderr, "--------------------\n");
	char **args;
	char **env_ptr;

	args = make_args(command);
	env_ptr = make_env_ptr(env_manager);
	exit(execve(command_path, args, env_ptr));
	return 0;
}
// TODO: 名前をいい感じに
int files_create(t_redirect_info *outputs)
{
	t_redirect_info *current;
	int last_fd;

	last_fd = -1;
	if (outputs == NULL)
		return STDOUT_FILENO;
	current = outputs;
	while (current != NULL)
	{
		close(last_fd);
		if (current->kind == REDIRECT_OUT_OVERWRITE)
			last_fd = open(current->arg, (O_WRONLY | O_CREAT) , 0644);
		else if (current->kind == REDIRECT_OUT_POST)
			last_fd = open(current->arg, (O_APPEND | O_CREAT | O_WRONLY) , 0644);
		else
			exit(1);
		// last_fd = open(current->arg, O_WRONLY);
		// fprintf(stderr, "last_fd %d\n", last_fd);
		if (last_fd == -1)
			return (-1);
		current = current->next;
	}
	return last_fd;
}

int pipe_exec(int before_fd, t_command *command, t_env_manager *env_manager)
{
	int pipe_fd[2];
	pid_t pid;
	int output_fd;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(&signal_info.pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
	{
		//child
		output_fd = files_create(command->outpus);
		if (output_fd == -1)
			return (-1);
		dup2(before_fd, STDIN_FILENO);
		dup2(pipe_fd[WRITE_FD], output_fd);
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		ft_exec(command, env_manager);
		close(pipe_fd[WRITE_FD]);
		close(pipe_fd[READ_FD]);
		close(output_fd);
		exit(127); // ?
	} else 
	{
		// parent
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		close(pipe_fd[WRITE_FD]);
		// TODO: append process id
	}
	return (pipe_fd[READ_FD]);
}

int non_pipe_exec(int before_fd, t_command *command, t_env_manager *env_manager)
{
	int output_fd;
	pid_t pid;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(&signal_info.pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
	{
		//child
		output_fd = files_create(command->outpus);
		if (output_fd == -1)
			return (-1);
		dup2(before_fd, STDIN_FILENO);
		// fprintf(stderr, "============output_fd=========\n");
		// fprintf(stderr, "%d\n", output_fd);
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		dup2(output_fd, STDOUT_FILENO);
		// close(STDERR_FILENO);
		ft_exec(command, env_manager);
		close(output_fd);
		exit(127);
	} else
	{
		// parent
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		return (STDIN_FILENO);
	}
	return (STDIN_FILENO);
}

int	command_exec(t_command *commands, t_env_manager *env_manager)
{
	t_command	*current;
	t_pid_list	*pid_current;
	int			before_fd;
	
	signal_info.status = EXECUTING_COMMAND;
	current = commands;
	before_fd = STDIN_FILENO;
	while (current != NULL)
	{
		if (current->next_pipe)
		{
			before_fd = pipe_exec(before_fd, current, env_manager);
		} else {
			before_fd = non_pipe_exec(before_fd, current, env_manager);
		}
		// TODO: before_fd == -1の時の処理
		current = current->next;
	}

	pid_current = signal_info.pid_list;
	while (pid_current != NULL)
	{
		// fprintf(stderr, "waiting\n");
		int tmp;
		wait(&tmp);
		fprintf(stderr, "process ret : %d\n", tmp);
		fprintf(stderr, "process ret / 256: %d\n", tmp / 256);
		pid_current = pid_current->next;
	}
	signal_info.status = UNDEFINED;
	free_pid_list(&signal_info.pid_list);
	return (0);
}
