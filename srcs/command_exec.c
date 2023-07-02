/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:11:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/02 16:46:40 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"

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
			before_fd = pipe_exec(before_fd, current, env_manager);
		else
			before_fd = non_pipe_exec(before_fd, current, env_manager);
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
