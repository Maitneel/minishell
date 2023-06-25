/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:57:19 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/24 06:55:42 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*free_redirect_info(t_redirect_info *front)
{
	t_redirect_info	*next;

	while (front != NULL)
	{
		next = front->next;
		free(front->arg);
		free(front);
		front = next;
	}
	return (NULL);
}

t_redirect_info	*new_redirect_info(void)
{
	t_redirect_info	*redirect_info;

	redirect_info = calloc(1, sizeof(t_redirect_info));
	if (redirect_info == NULL)
	{
		return (NULL);
	}
	return (redirect_info);
}

void	push_back_redirect_info(t_redirect_info **front, t_redirect_info *node)
{
	t_redirect_info	*current;

	if (front == NULL)
	{
		return ;
	}
	if (*front == NULL)
	{
		*front = node;
		return ;
	}
	current = *front;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = node;
}

void	*free_args_list(t_args_list *front)
{
	t_args_list	*next;

	while (front != NULL)
	{
		next = front->next;
		free(front->string);
		free(front);
		front = next;
	}
	return (NULL);
}

t_args_list	*new_args_list(char *string)
{
	t_args_list	*args;

	args = calloc(1, sizeof(t_args_list));
	if (args == NULL)
	{
		return (NULL);
	}
	args->string = strdup(string);
	if (args->string == NULL)
	{
		free(args);
		return (NULL);
	}
	return (args);
}

void	push_back_args_list(t_args_list **front, t_args_list *node)
{
	t_args_list	*current;

	if (front == NULL)
	{
		return ;
	}
	if (*front == NULL)
	{
		*front = node;
		return ;
	}
	current = *front;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = node;
}

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

	command = calloc(sizeof(t_command), 1);
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

bool	is_in_redirect_word(char *string)
{
	if (strcmp(string, "<") == 0)
	{
		return (true);
	}
	if (strcmp(string, "<<") == 0)
	{
		return (true);
	}
	return (false);
}

bool	is_out_redirect_word(char *string)
{
	if (strcmp(string, ">") == 0)
	{
		return (true);
	}
	if (strcmp(string, ">>") == 0)
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

bool	add_redirect_to_command(t_command *command, t_token *front_token)
{
	t_redirect_info	*redirect_info;

	if (front_token->next == NULL || is_redirect_word(front_token->next->word))
	{
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

typedef enum e_return_status
{
	SUCCESS = 3000,
	TO_RETURN,
	TO_BREAK
}				t_return_status;

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
	else if (is_redirect_word((*front_token)->word))
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

t_command	*parse(t_token_manager *token_manager)
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
	return (front_command);
}

// /*
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
