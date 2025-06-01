/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:11:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/22 17:56:29 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "signal_handler.h"
#include <sys/fcntl.h>
#include <sys/wait.h>

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

void	wait_child_proceess(t_pid_list *pid_list, t_env_manager *env_manager)
{
	t_pid_list	*pid_current;

	pid_current = pid_list;
	while (pid_current != NULL)
	{
		waitpid(pid_current->pid, &env_manager->exit_status, 0);
		env_manager->exit_status = get_exit_code(env_manager->exit_status);
		pid_current = pid_current->next;
	}
}

void	exec_builtin_no_fork(t_command *command, t_env_manager *env_manager)
{
	int				output_fd;
	char			**args;

	if (can_open_input_files(command->inputs, env_manager) == -1)
		return ;
	output_fd = files_create(command->outpus);
	if (output_fd == -1)
	{
		env_manager->exit_status = 1;
		return ;
	}
	args = make_args(command);
	env_manager->exit_status = \
			exec_builtin(command, args, env_manager, output_fd);
	free_string_array(args);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
}

int	command_exec(t_command *commands, t_env_manager *env_manager)
{
	t_command	*current;
	t_pid_list	*pids;
	int			before_fd;

	pids = NULL;
	current = commands;
	before_fd = STDIN_FILENO;
	register_signal_handler(cmd_exec_signal_handler);
	if (is_builtin(current->command_name) && !current->next_pipe)
	{
		exec_builtin_no_fork(current, env_manager);
		unlink_tempfile(commands);
		return (0);
	}
	while (current != NULL)
	{
		if (current->next_pipe)
			before_fd = pipe_exec(before_fd, current, &pids, env_manager);
		else
			before_fd = non_pipe_exec(before_fd, current, &pids, env_manager);
		current = current->next;
	}
	exec_end_processing(pids, commands, env_manager);
	return (0);
}
