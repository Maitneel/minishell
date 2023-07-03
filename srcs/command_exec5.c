/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:57:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/03 21:12:10 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"

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

	input_fd = files_dup2_stdin(command->inputs);
	if (input_fd == -1)
		exit(1);
	output_fd = files_create(command->outpus);
	if (output_fd == -1)
		exit(1);
	if (command->command_name == NULL)
		exit(0);
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
	exit(127);
}
