/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:57:19 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/16 20:43:17 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenize.h"
#include "print_lib.h"
#include "ft_xcalloc.h"

#include <stdlib.h>

void	set_redirect_kind(char *token_word, t_redirect_info *redirect_info)
{
	if (ft_strcmp(token_word, "<") == 0)
	{
		redirect_info->kind = REDIRECT_IN;
	}
	else if (ft_strcmp(token_word, "<<") == 0)
	{
		redirect_info->kind = REDIRECT_HEAR_DOC;
	}
	else if (ft_strcmp(token_word, ">") == 0)
	{
		redirect_info->kind = REDIRECT_OUT_OVERWRITE;
	}
	else if (ft_strcmp(token_word, ">>") == 0)
	{
		redirect_info->kind = REDIRECT_OUT_POST;
	}
}

t_return_status	parser_helper(t_token **front_token, t_command **front_command,
		t_command **command, t_env_manager *env_manager)
{
	if ((*front_token)->kind == PIPE_KIND)
	{
		push_back_command(front_command, (*command));
		(*command)->next_pipe = true;
		(*command) = new_command();
		if ((*command) == NULL)
			return (TO_RETURN);
	}
	else if ((*front_token)->kind == REDIRECT_KIND)
	{
		if (add_redirect(*command, *front_token, env_manager) == false)
			return (TO_RETURN);
		(*front_token) = (*front_token)->next;
		if ((*front_token) == NULL || (*command)->is_error == true)
			return (TO_BREAK);
	}
	else
	{
		if (add_command_name_or_args((*command), (*front_token)) == false)
			return (TO_RETURN);
	}
	(*front_token) = (*front_token)->next;
	return (SUCCESS);
}

t_command	*parse(t_token_manager *token_manager, t_env_manager *env_manager)
{
	t_command		*cmd;
	t_command		*f_cmd;
	t_token			*f_token;
	t_return_status	return_status;

	f_cmd = NULL;
	cmd = new_command();
	if (cmd == NULL)
		return (free_command(cmd));
	f_token = token_manager->front;
	while (f_token != NULL && f_token->kind != SYNTAX_ERROR)
	{
		return_status = parser_helper(&f_token, &f_cmd, &cmd, env_manager);
		if (return_status == TO_RETURN)
			return (free_command(f_cmd));
		if (return_status == TO_BREAK)
			break ;
	}
	push_back_command(&f_cmd, cmd);
	if (f_token != NULL || cmd->is_error == true)
		f_cmd->is_error = true;
	expand_here_doc(f_cmd, env_manager);
	return (f_cmd);
}
