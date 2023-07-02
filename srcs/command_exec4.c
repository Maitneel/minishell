/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:41:08 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/02 16:41:24 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"

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
