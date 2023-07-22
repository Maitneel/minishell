/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:41:08 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/22 18:08:55 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include <stdio.h>

int	ft_exec(t_command *command, t_env_manager *env_manager)
{
	char	*command_path;
	char	**args;
	char	**env_ptr;

	if (ft_strcmp(command->command_name, "") == 0)
		exit(0);
	args = make_args(command);
	env_ptr = make_env_ptr(env_manager);
	if (is_builtin(command->command_name))
		exit(exec_builtin(command, args, env_manager, STDOUT_FILENO));
	command_path = find_path(command, env_manager);
	if (command_path == NULL)
	{
		put_command_not_found(command->command_name);
		return (-1);
	}
	execve(command_path, args, env_ptr);
	write(STDERR_FILENO, "minishell: ", 12);
	perror(command_path);
	exit(126);
	return (0);
}

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
			last_fd = open(current->arg, (O_WRONLY | O_CREAT | O_TRUNC), 0644);
		else if (current->kind == REDIRECT_OUT_POST)
			last_fd = open(current->arg, (O_APPEND | O_CREAT | O_WRONLY), 0644);
		else
			exit(1);
		if (last_fd == -1)
		{
			write(STDERR_FILENO, "minishell: ", 12);
			perror(current->arg);
			return (-1);
		}
		current = current->next;
	}
	return (last_fd);
}

int	files_dup2_stdin(t_redirect_info *inputs)
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
		fd = open(current->arg, O_RDONLY);
		if (fd == -1)
		{
			write(STDERR_FILENO, "minishell: ", 12);
			perror(current->arg);
			return (-1);
		}
		current = current->next;
	}
	dup2(fd, STDIN_FILENO);
	return (fd);
}

int	pipe_exec(int before_fd, t_command *command, t_pid_list **pid_list,
		t_env_manager *env_manager)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
		pipe_child_exec(before_fd, pipe_fd, command, env_manager);
	else
	{
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		close(pipe_fd[WRITE_FD]);
	}
	return (pipe_fd[READ_FD]);
}

int	non_pipe_exec(int before_fd, t_command *command, t_pid_list **pid_list,
		t_env_manager *env_manager)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
		non_pipe_child_exec(before_fd, command, env_manager);
	else
	{
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		return (STDIN_FILENO);
	}
	return (STDIN_FILENO);
}
