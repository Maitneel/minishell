/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:58:12 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:21:02 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include "print_lib.h"

bool	is_in_redirect_word(char *string)
{
	if (ft_strcmp(string, "<") == 0)
	{
		return (true);
	}
	if (ft_strcmp(string, "<<") == 0)
	{
		return (true);
	}
	return (false);
}

bool	is_out_redirect_word(char *string)
{
	if (ft_strcmp(string, ">") == 0)
	{
		return (true);
	}
	if (ft_strcmp(string, ">>") == 0)
	{
		return (true);
	}
	return (false);
}

bool	is_redirect_word(char *string)
{
	if (is_in_redirect_word(string) || is_out_redirect_word(string))
	{
		return (true);
	}
	return (false);
}

bool	add_redirect_to_command(t_command *command, t_token *front_token)
{
	t_redirect_info	*redirect_info;

	if (front_token->next == NULL || front_token->next->kind == REDIRECT_KIND)
	{
		print_syntax_error(front_token->next);
		command->is_error = true;
		return (true);
	}
	redirect_info = new_redirect_info();
	if (redirect_info == NULL)
		return (false);
	redirect_info->arg = strdup(front_token->next->word);
	if (redirect_info->arg == NULL)
	{
		free(redirect_info);
		// ここ型絶対違うのにコンパイル通るの謎 
		return (free_command(command));
	}
	set_redirect_kind(front_token->word, redirect_info);
	if (is_in_redirect_word(front_token->word))
		push_back_redirect_info(&command->inputs, redirect_info);
	else
		push_back_redirect_info(&command->outpus, redirect_info);
	return (true);
}

bool	add_command_name_or_args(t_command *command,
								t_token *front_token)
{
	t_args_list	*args;

	if (command->command_name == NULL)
	{
		command->command_name = strdup(front_token->word);
		if (command->command_name == NULL)
		{
			return (false);
		}
	}
	else
	{
		args = new_args_list(front_token->word);
		if (args == NULL)
		{
			return (false);
		}
		push_back_args_list(&command->args_list, args);
	}
	return (true);
}
