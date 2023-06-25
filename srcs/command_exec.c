/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:11:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/01 18:39:23 by taksaito         ###   ########.fr       */
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
		"env",
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
	// libftの関数はxcallocに置き換えていないので、これはexitする必要がある
	if (paths == NULL)
		ft_exit(ALOCATE_ERROR);
	i = 0;
	while (paths[i] != NULL)
	{
		absolute_path = make_path(paths[i], command->command_name);
		if (absolute_path == NULL)
			ft_exit(ALOCATE_ERROR);
			// return (free_string_array(paths));
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

int	ft_exec(t_command *command, t_env_manager *env_manager)
{
	char	*command_path;
	char	**args;
	char	**env_ptr;

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
 	execve(command_path, args, env_ptr);
	write(STDERR_FILENO, "minishell: ", 12);
	perror(command_path);
	// コマンドは見つかったが実行できなかった(権限がないとか)の時の終了コード
	exit(126);
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

	// pipe_fd == -1の時のエラー処理
	if (pipe(pipe_fd) == -1)
	{
		// エラー処理(親プロセスでの処理になる)
		// exit するのか、そのままpromptに戻すのか
	}
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
		// dup2のエラー処理までするかどうか....
		dup2(before_fd, input_fd);
		// dup2(pipe_fd[WRITE_FD], output_fd);
		dup2(pipe_fd[WRITE_FD], STDOUT_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		ft_exec(command, env_manager);
		close(pipe_fd[WRITE_FD]);
		close(pipe_fd[READ_FD]);
		close(output_fd);
		close(input_fd);
		// コマンドが見つからなかったのか、コマンドは見つかったが実行できなかったかによって、exitするコードが変わると思う 
		exit(127); // ?
	}
	else
	{
		// parent
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		close(pipe_fd[WRITE_FD]);
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
		fprintf(stderr, "output_fd : '%d'\n", output_fd);
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
		// ここのelse外せるかも
		// parent
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		return (STDIN_FILENO);
	}
	return (STDIN_FILENO);
}

int get_exit_code(int n)
{
	if (n % 256 == 0)
		return n / 256;
	else
		return (n % 256 + 128);
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
		wait(&env_manager->exit_status);
		env_manager->exit_status = get_exit_code(env_manager->exit_status);
		pid_current = pid_current->next;
	}
	g_signal_info.status = UNDEFINED;
	free_pid_list(&g_signal_info.pid_list);
	return (0);
}
