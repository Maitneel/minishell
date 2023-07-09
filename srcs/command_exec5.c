/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:57:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 20:03:07 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include <stdio.h>

void	non_pipe_child_exec(int before_fd, t_command *command,
		t_env_manager *env_manager)
{
	int	input_fd;
	int	output_fd;

	dup2(before_fd, STDIN_FILENO);
	if (before_fd != STDIN_FILENO)
		close(before_fd);
	input_fd = files_dup2_stdin(command->inputs);
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

void	pipe_child_exec(int before_fd, int pipe_fd[2], t_command *command,
		t_env_manager *env_manager)
{
	int	input_fd;
	int	output_fd;

	dup2(before_fd, STDIN_FILENO);
	input_fd = files_dup2_stdin(command->inputs);
	if (input_fd == -1)
		exit(1);
	output_fd = files_create(command->outpus);
	if (output_fd == -1)
		exit(1);
	if (command->command_name == NULL)
		exit(0);
	dup2(pipe_fd[WRITE_FD], STDOUT_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	if (before_fd != STDIN_FILENO)
		close(before_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
	close(pipe_fd[WRITE_FD]);
	close(pipe_fd[READ_FD]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	ft_exec(command, env_manager);
	close(STDIN_FILENO);
	exit(127);
}

int	can_open_input_files(t_redirect_info *input_current,
							t_env_manager *env_manager)
{
	int	input_fd;

	while (input_current != NULL)
	{
		input_fd = open(input_current->arg, O_RDONLY);
		if (input_fd == -1)
		{
			write(STDERR_FILENO, "minishell: ", 12);
			perror(input_current->arg);
			env_manager->exit_status = 1;
			return (-1);
		}
		close(input_fd);
		input_current = input_current->next;
	}
	return (0);
}
