/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:57:19 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/08 17:19:45 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenize.h"
#include "print_lib.h"
#include "ft_xcalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	set_redirect_kind(char *token_word, t_redirect_info *redirect_info)
{
	if (strcmp(token_word, "<") == 0)
	{
		redirect_info->kind = REDIRECT_IN;
	}
	else if (strcmp(token_word, "<<") == 0)
	{
		redirect_info->kind = REDIRECT_HEAR_DOC;
	}
	else if (strcmp(token_word, ">") == 0)
	{
		redirect_info->kind = REDIRECT_OUT_OVERWRITE;
	}
	else if (strcmp(token_word, ">>") == 0)
	{
		redirect_info->kind = REDIRECT_OUT_POST;
	}
}

t_return_status	parser_helper(t_token **front_token, t_command **front_command,
		t_command **command)
{
	if (strcmp((*front_token)->word, "|") == 0)
	{
		push_back_command(front_command, (*command));
		(*command)->next_pipe = true;
		(*command) = new_command();
		if ((*command) == NULL)
			return (TO_RETURN);
	}
	else if ((*front_token)->kind == REDIRECT_KIND)
	{
		if (add_redirect_to_command((*command), (*front_token)) == false)
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
	t_command		*command;
	t_command		*front_command;
	t_token			*front_token;
	t_return_status	return_status;

	front_command = NULL;
	command = new_command();
	if (command == NULL)
		return (free_command(command));
	front_token = token_manager->front;
	while (front_token != NULL && front_token->kind != SYNTAX_ERROR)
	{
		return_status = parser_helper(&front_token, &front_command, &command);
		if (return_status == TO_RETURN)
			return (free_command(front_command));
		if (return_status == TO_BREAK)
			break ;
	}
	push_back_command(&front_command, command);
	if (front_token != NULL || command->is_error == true)
		front_command->is_error = true;
	expand_here_doc(front_command, env_manager);
	return (front_command);
}

/*
void	print_command(t_command *command)
{
	t_redirect_info	*redirect;
	t_args_list		*args;

	fprintf(stderr, "\x1b[36m");
	while (command != NULL)
	{
		fprintf(stderr, "--------------------------------------\n");
		fprintf(stderr, "%-13s : '%s'\n", "command_name",
				command->command_name);
		fprintf(stderr, "%-13s : ", "input list");
		redirect = command->inputs;
		while (redirect != NULL)
		{
			fprintf(stderr, "[%d, '%s'], ", redirect->kind, redirect->arg);
			redirect = redirect->next;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%-13s : ", "output list");
		redirect = command->outpus;
		while (redirect != NULL)
		{
			fprintf(stderr, "[%d, '%s'], ", redirect->kind, redirect->arg);
			redirect = redirect->next;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%-13s : ", "args");
		args = command->args_list;
		while (args != NULL)
		{
			fprintf(stderr, "%s ", args->string);
			args = args->next;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%-13s : '%d'\n", "next_pipe", command->next_pipe);
		command = command->next;
	}
	fprintf(stderr, "--------------------------------------\n");
	fprintf(stderr, "\x1b[39m");
}
// */
