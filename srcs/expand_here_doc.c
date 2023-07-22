/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 06:58:37 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 17:51:40 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "env.h"
#include "parser.h"
#include "signal_handler.h"
#include <unistd.h>
#include <stdio.h>

int	set_heredoc_error(t_command *command, t_env_manager *env_manager)
{
	env_manager->exit_status = 1;
	command->is_heredoc_error = true;
	return (0);
}

int	processing_heredoc(t_redirect_info *current, t_env_manager *env_manager)
{
	char	*file_name;

	file_name = here_doc(current, env_manager);
	register_signal_handler(signal_handler);
	if (file_name == NULL)
		return (-1);
	free(current->arg);
	current->arg = file_name;
	current->kind = EXPANDED_HEREDOC;
	return (0);
}

int	expand_here_of_one_command(t_command *command, t_env_manager *env_manager)
{
	t_redirect_info	*current;

	current = command->inputs;
	while (current != NULL)
	{
		if (current->kind == REDIRECT_HEAR_DOC)
		{
			if (processing_heredoc(current, env_manager) == -1)
			{
				return (-1);
			}
			if (g_recived_signal_id == SIGINT)
			{
				g_recived_signal_id = -1;
				return (set_heredoc_error(command, env_manager));
			}
		}
		current = current->next;
	}
	return (0);
}

int	expand_here_doc(t_command *command, t_env_manager *env_manager)
{
	t_command	*current_command;

	if (command == NULL)
		return (-2);
	current_command = command;
	while (current_command != NULL)
	{
		if (expand_here_of_one_command(current_command, env_manager) != 0)
			exit(1);
		if (current_command->is_heredoc_error == true)
		{
			unlink_tempfile(command);
			command->is_heredoc_error = true;
			return (-1);
		}
		current_command = current_command->next;
	}
	return (0);
}
