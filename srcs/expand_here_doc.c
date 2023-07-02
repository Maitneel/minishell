/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 06:58:37 by dummy             #+#    #+#             */
/*   Updated: 2023/07/03 08:16:31 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "env.h"
#include "parser.h"

int	expand_here_of_one_command(t_command *command, t_env_manager *env_manager)
{
	t_redirect_info	*current;
	char			*file_name;

	current = command->inputs;
	while (current != NULL)
	{
		if (current->kind == REDIRECT_HEAR_DOC)
		{
			file_name = here_doc(current, env_manager);
			if (file_name == NULL)
				return (-1);
			free(current->arg);
			current->arg = file_name;
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
		{
			// TODO error handring
			// heredocが失敗した時にどういう処理をするか
			// 今までは小プロセスで実行していたが、ここでは親プロセスでの実行になるので
			// 安易にexitしていいのか
		}
		current_command = current_command->next;
	}
	return (0);
}
