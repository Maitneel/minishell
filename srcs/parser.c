/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:57:19 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/28 20:10:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenize.h"
#include <stdlib.h>
#include <string.h>

t_command *new_command(void)
{
    t_command *command;

    command = calloc(sizeof(t_command), 1);
    if (command == NULL)
    {
        return NULL;
    }
    return command;
}

void *free_command(t_command *command)
{
    // TODO
    (void)(command);
    return NULL;
}

void push_back_command(t_command *front, t_command *command)
{
    (void)front;
    (void)command;
}

t_redirect_info *new_redirect_info(void)
{
    return NULL;
}

void push_back_redirect_info(t_redirect_info *front, t_redirect_info *node)
{
    (void)front;
    (void)(node);
}

t_args_list *new_args(char *string)
{
    (void)string;
    return NULL;
}

void push_back_args_list(t_args_list *front, t_args_list *node)
{
    (void)front;
    (void)node;
}

t_command   *parse(t_token_manager *token_manager)
{
    t_command *command;
    t_command *front_command;
    t_token *front_token;
    t_redirect_info *redirect_info;
    t_args_list *args;

    front_command = new_command();
    front_token = token_manager->front;
    while (front_token != NULL)
    {
        if (front_token->kind == SYNTAX_ERROR)
        {
            command->is_error = true;
            break;
        }
        if (strcmp(front_token->word, "|") == 0)
        {
            push_back_command(front_command, command);
            command->next_pipe = true;
            command = new_command();
            if (command == NULL)
            {
                return free_command(front_command);
            }
        }
        if (strcmp(front_token->word, "<") == 0 || strcmp(front_token->word, "<<") == 0 || strcmp(front_token->word, ">") == 0 || strcmp(front_token->word, ">>") == 0)
        {
            if (front_token->next == NULL)
            {
                command->is_error = true;
                break;
                // return free_command(front_command);
            }
            redirect_info = new_redirect_info();
            if (redirect_info == NULL)
            {
                return free_command(front_command);
            }
            redirect_info->arg = front_token->next->word;
            if (strcmp(front_token->word, "<") == 0)
            {
                redirect_info->kind = REDIRECT_IN;
            }
            else if (strcmp(front_token->word, "<<") == 0)
            {
                redirect_info->kind = REDIRECT_HEAR_DOC;
                redirect_info->arg = "STDIN";
            }
            else if (strcmp(front_token->word, ">") == 0)
            {
                redirect_info->kind = REDIRECT_OUT_OVERWRITE;
            }
            else if (strcmp(front_token->word, ">>") == 0)
            {
                redirect_info->kind = REDIRECT_OUT_POST;
            }
            if (strcmp(front_token->word, "<") == 0 || strcmp(front_token->word, "<<") == 0)
            {
                push_back_redirect_info(command->inputs, redirect_info);
            } 
            else
            {
                push_back_redirect_info(command->outpus, redirect_info);
            }
            front_token = front_token->next;
            if (front_token == NULL)
            {
                break;
            }
        }
        else 
        {
            args = new_args(front_token->word);
            if (args == NULL)
            {
                return free_command(front_command);
            }
            push_back_args_list(&command->args_list, args);
        }
        front_token = front_token->next;
    }
    push_back_command(front_command, command);
    command = front_command->next;
    free(front_command);
    return command;
}
