/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:08:01 by dummy             #+#    #+#             */
/*   Updated: 2023/07/16 21:57:44 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_xcalloc.h"
#include <stdlib.h>

void	*free_command(t_command *command)
{
	t_command	*next;
	size_t		i;

	while (command != NULL)
	{
		next = command->next;
		free(command->command_name);
		i = 0;
		while (command->args != NULL && command->args[i] != NULL)
		{
			free(command->args[i]);
			i++;
		}
		free_redirect_info(command->inputs);
		free_redirect_info(command->outpus);
		free_args_list(command->args_list);
		free(command);
		command = next;
	}
	return (NULL);
}

t_command	*new_command(void)
{
	t_command	*command;

	command = ft_xcalloc(sizeof(t_command), 1);
	if (command == NULL)
	{
		return (NULL);
	}
	return (command);
}

void	push_back_command(t_command **front, t_command *command)
{
	t_command	*current;

	if (front == NULL)
	{
		return ;
	}
	if (*front == NULL)
	{
		*front = command;
		return ;
	}
	current = *front;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = command;
}

t_command	*syntax_error_in_front(t_token *f_token,
					t_command *cmd, t_env_manager *env_manager)
{
	print_syntax_error(f_token);
	cmd->is_error = true;
	env_manager->exit_status = 1;
	return (cmd);
}
