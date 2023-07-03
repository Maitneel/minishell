/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:11:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/03 19:03:11 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"

int	get_exit_code(int n)
{
	if (n % 256 == 0)
		return (n / 256);
	else
		return (n % 256 + 128);
}

void	unlink_tempfile(t_command *command)
{
	t_command		*current_command;
	t_redirect_info	*current_inputs;

	current_command = command;
	while (current_command != NULL)
	{
		current_inputs = current_command->inputs;
		while (current_inputs != NULL)
		{
			if (current_inputs->kind == EXPANDED_HEREDOC)
				unlink(current_inputs->arg);
			current_inputs = current_inputs->next;
		}
		current_command = current_command->next;
	}
}

void	wait_child_proceess(t_env_manager *env_manager)
{
	t_pid_list	*pid_current;

	pid_current = g_signal_info.pid_list;
	while (pid_current != NULL)
	{
		wait(&env_manager->exit_status);
		env_manager->exit_status = get_exit_code(env_manager->exit_status);
		pid_current = pid_current->next;
	}
}

int	command_exec(t_command *commands, t_env_manager *env_manager)
{
	t_command	*current;
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
		current = current->next;
	}
	wait_child_proceess(env_manager);
	g_signal_info.status = UNDEFINED;
	free_pid_list(&g_signal_info.pid_list);
	unlink_tempfile(commands);
	return (0);
}
