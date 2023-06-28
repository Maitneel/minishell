/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:11:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/28 22:40:55 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "command_exec.h"
#include "env.h"
#include "expand_env.h"
#include "ft_signal.h"
#include "get_next_line.h"
#include "libft.h"
#include "ft_xcalloc.h"
#include "parser.h"
#include "tokenize.h"
#include "print_lib.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WRITE_FD 1
#define READ_FD 0

bool	is_builtin(char *command)
{
	size_t		i;
	const char	*commands[] = {
		"echo",
		"export",
		"pwd",
		"cd",
		"echo",
		"pwd",
		"unset",
		"exit",
		NULL};

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp((char *)commands[i], command) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	*free_string_array(char **string_array)
{
	size_t	i;

	i = 0;
	while (string_array[i] != NULL)
	{
		free(string_array[i]);
		i++;
	}
	free(string_array);
	return (NULL);
}

size_t	get_args_list_size(t_command *command)
{
	size_t		size;
	t_args_list	*args_list;

	args_list = command->args_list;
	size = 0;
	while (args_list != NULL)
	{
		args_list = args_list->next;
		size++;
	}
	return (size);
}

char	*expand_line(char *line, t_env_manager *env_manager)
{
	t_string	struct_line;
	t_string	expanded;

	struct_line.data = line;
	struct_line.length = strlen(line);
	struct_line.max_length = struct_line.length;
	if (expand_env(&expanded, &struct_line, env_manager) == NULL)
		return (NULL);
	return (expanded.data);
}

int	expand_and_write(int fd, t_redirect_info *info, t_env_manager *env_manager)
{
	char	*line;
	char	*expanded;
	char	*end_text;

	end_text = ft_strjoin(info->arg, "\n");
	if (end_text == NULL)
		return (-1);
	while (true)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (strcmp(line, end_text) == 0)
			break ;
		expanded = expand_line(line, env_manager);
		free(line);
		if (expanded == NULL)
			return (-1);
		if (write(fd, expanded, strlen(expanded)) == -1)
		{
			free(expanded);
			return (-1);
		}
		free(expanded);
	}
	free(line);
	free(end_text);
	return (fd);
}

int	here_doc(t_redirect_info *info, t_env_manager *env_manager)
{
	int		output_fd;
	int		input_fd;
	char	*file_name;

	file_name = generate_no_exist_file_name("/tmp/here_doc_tmp");
	if (file_name == NULL)
		return (-1);
	output_fd = open(file_name, (O_WRONLY | O_CREAT));
	if (output_fd == -1)
	{
		free(file_name);
		return (-1);
	}
	input_fd = open(file_name, (O_RDONLY));
	unlink(file_name);
	free(file_name);
	if (input_fd == -1)
	{
		close(output_fd);
		return (-1);
	}
	if (expand_and_write(output_fd, info, env_manager) == -1)
		return (-1);
	return (input_fd);
}

char	**make_args(t_command *command)
{
	size_t		args_size;
	char		**args_array;
	t_args_list	*args_list;
	size_t		i;

	args_size = get_args_list_size(command) + 1;
	args_array = ft_xcalloc(args_size + 1, sizeof(char *));
	if (args_array == NULL)
		return (NULL);
	args_array[0] = strdup(command->command_name);
	if (args_array[0] == NULL)
		return (free_string_array(args_array));
	i = 1;
	args_list = command->args_list;
	while (args_list != NULL)
	{
		args_array[i] = strdup(args_list->string);
		if (args_array[i] == NULL)
			return (free_string_array(args_array));
		i++;
		args_list = args_list->next;
	}
	return (args_array);
}

char	*make_path(const char *path, const char *command)
{
	char	*slashed;
	char	*joined;

	if (path == NULL || command == NULL)
		return (NULL);
	slashed = ft_strjoin(path, "/");
	if (slashed == NULL)
		return (NULL);
	joined = ft_strjoin(slashed, command);
	free(slashed);
	return (joined);
}

char	*find_path(t_command *command, t_env_manager *env_manager)
{
	t_env	*path_env;
	size_t	i;
	char	*absolute_path;
	char	**paths;

	// 絶対パスかのチェック
	if (access(command->command_name, F_OK) == 0)
		return (strdup(command->command_name));
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
	return (NULL);
}

int	exec_builtin(t_command *command, char **args, t_env_manager *env_manager)
{
	if (ft_strcmp(command->command_name, "echo") == 0)
		return (command_echo(args));
	if (ft_strcmp(command->command_name, "cd") == 0)
		return (command_cd(args));
	if (ft_strcmp(command->command_name, "pwd") == 0)
		return (command_pwd());
	if (ft_strcmp(command->command_name, "env") == 0)
		return (command_env(env_manager, args));
	if (ft_strcmp(command->command_name, "export") == 0)
		return (command_export(env_manager, args));
	if (ft_strcmp(command->command_name, "unset") == 0)
		return (command_unset(env_manager, args));
	if (ft_strcmp(command->command_name, "exit") == 0)
		return (command_exit(env_manager, args));
	return (0);
}

int	ft_exec(t_command *command, t_env_manager *env_manager)
{
	char	*command_path;
	char	**args;
	char	**env_ptr;

	// TODO: envの$?に入れる　
	// fprintf(stderr, "--------------------\n");
	args = make_args(command);
	env_ptr = make_env_ptr(env_manager);
	if (is_builtin(command->command_name))
		exit(exec_builtin(command, args, env_manager));
	command_path = find_path(command, env_manager);
	if (command_path == NULL)
	{
		put_command_not_found(command->command_name);
		return (-1);
	}
	exit(execve(command_path, args, env_ptr));
	return (0);
}
// TODO: 名前をいい感じに

int	files_create(t_redirect_info *outputs)
{
	t_redirect_info	*current;
	int				last_fd;

	last_fd = -1;
	if (outputs == NULL)
		return (STDOUT_FILENO);
	current = outputs;
	while (current != NULL)
	{
		close(last_fd);
		if (current->kind == REDIRECT_OUT_OVERWRITE)
			last_fd = open(current->arg, (O_WRONLY | O_CREAT), 0644);
		else if (current->kind == REDIRECT_OUT_POST)
			last_fd = open(current->arg, (O_APPEND | O_CREAT | O_WRONLY), 0644);
		else
			exit(1);
		if (last_fd == -1)
			return (-1);
		current = current->next;
	}
	return (last_fd);
}

int	files_dup2_stdin(t_redirect_info *inputs, t_env_manager *env_manager)
{
	t_redirect_info	*current;
	int				fd;

	current = inputs;
	fd = -1;
	if (inputs == NULL)
		return (STDIN_FILENO);
	while (current != NULL)
	{
		close(fd);
		if (current->kind == REDIRECT_IN)
			fd = open(current->arg, O_RDONLY);
		else if (current->kind == REDIRECT_HEAR_DOC)
			fd = here_doc(current, env_manager);
		if (fd == -1)
			return (-1);
		current = current->next;
	}
	dup2(fd, STDIN_FILENO);
	return (fd);
}

int	pipe_exec(int before_fd, t_command *command, t_env_manager *env_manager)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		output_fd;
	int		input_fd;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(&g_signal_info.pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
	{
		//child
		input_fd = files_dup2_stdin(command->inputs, env_manager);
		if (input_fd == -1)
			exit(1);
		output_fd = files_create(command->outpus);
		if (output_fd == -1)
			exit(1);
		if (command->command_name == NULL)
			exit(0);
		dup2(before_fd, input_fd);
		dup2(pipe_fd[WRITE_FD], output_fd);
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		ft_exec(command, env_manager);
		close(pipe_fd[WRITE_FD]);
		close(pipe_fd[READ_FD]);
		close(output_fd);
		close(input_fd);
		exit(127); // ?
	}
	else
	{
		// parent
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		close(pipe_fd[WRITE_FD]);
		// TODO: append process id
	}
	return (pipe_fd[READ_FD]);
}

int	non_pipe_exec(int before_fd, t_command *command, t_env_manager *env_manager)
{
	int		input_fd;
	int		output_fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(&g_signal_info.pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
	{
		//child
		dup2(before_fd, STDIN_FILENO);
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		input_fd = files_dup2_stdin(command->inputs, env_manager);
		if (input_fd == -1)
			exit(1);
		output_fd = files_create(command->outpus);
		if (output_fd == -1)
			exit(1);
		if (command->command_name == NULL)
			exit(0);
		dup2(output_fd, STDOUT_FILENO);
		ft_exec(command, env_manager);
		close(output_fd);
		close(input_fd);
		exit(127);
	}
	else
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

	g_signal_info.status = EXECUTING_COMMAND;
	current = commands;
	before_fd = STDIN_FILENO;
	while (current != NULL)
	{
		if (current->next_pipe)
		{
			before_fd = pipe_exec(before_fd, current, env_manager);
		}
		else
		{
			before_fd = non_pipe_exec(before_fd, current, env_manager);
		}
		// TODO: before_fd == -1の時の処理
		current = current->next;
	}
	pid_current = g_signal_info.pid_list;
	while (pid_current != NULL)
	{
		// fprintf(stderr, "waiting\n");
		wait(&env_manager->exit_status);
		// fprintf(stderr, "process ret : %d\n", env_manager->exit_status);
		// fprintf(stderr, "process ret / 256: %d\n", env_manager->exit_status
		// 		/ 256);
		env_manager->exit_status /= 256;
		pid_current = pid_current->next;
	}
	g_signal_info.status = UNDEFINED;
	free_pid_list(&g_signal_info.pid_list);
	return (0);
}
