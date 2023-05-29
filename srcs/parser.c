/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:57:19 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/29 16:41:48 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenize.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

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

void *free_redirect_info(t_redirect_info *front)
{
    t_redirect_info *next;

    while (front != NULL)
    {
        next = front->next;
        free(front->arg);
        free(front);
        front = next;
    }
    return NULL;
}

void *free_command(t_command *command)
{
    t_command *next;
    size_t i;
    while (command != NULL)
    {
        next = command->next;
        free(command->command_name);
        i = 0;
        while(command->args != NULL && command->args[i] != NULL)
        {
            free(command->args[i]);
            i++;
        }
        free_redirect_info(command->inputs);
        free_redirect_info(command->outpus);
        free(command);
        command = next;
    }
    return NULL;
}

void push_back_command(t_command *front, t_command *command)
{
    if (front == NULL)
    {
        return ;
    }
    while (front->next != NULL)
    {
        front = front->next;
    }
    front->next = command;
}

t_redirect_info *new_redirect_info(void)
{
    t_redirect_info *redirect_info;
    redirect_info = calloc(1, sizeof(t_redirect_info));
    if (redirect_info == NULL)
    {
        return NULL;
    }
    return redirect_info;
}

void push_back_redirect_info(t_redirect_info *front, t_redirect_info *node)
{
    if (front == NULL)
    {
        return ;
    }
    while (front->next != NULL)
    {
        front = front->next;
    }
    front->next = node;
}

t_args_list *new_args(char *string)
{
    t_args_list *args;
    args = calloc(1, sizeof(t_args_list));
    if (args == NULL)
    {
        return NULL;
    }
    args->string = strdup(string);
    if (args->string == NULL)
    {
        free(args);
        return NULL;
    }
    
    return args;
}

void push_back_args_list(t_args_list *front, t_args_list *node)
{
    if (front == NULL)
    {
        return ;
    }
    while (front->next != NULL)
    {
        front = front->next;
    }
    front->next = node;
}

t_command   *parse(t_token_manager *token_manager)
{
    t_command *command;
    t_command *front_command;
    t_token *front_token;
    t_redirect_info *redirect_info;
    t_args_list *args;

    front_command = new_command();
    command = new_command();
    if (front_command == NULL || command == NULL)
    {
        free_command(front_command);
        return free_command(command);
    }
    
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
        else if (strcmp(front_token->word, "<") == 0 || strcmp(front_token->word, "<<") == 0 || strcmp(front_token->word, ">") == 0 || strcmp(front_token->word, ">>") == 0)
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
            redirect_info->arg = strdup(front_token->next->word);
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
            printf("redirect_info : '%s'\n", redirect_info->arg);
            if (strcmp(front_token->word, "<") == 0 || strcmp(front_token->word, "<<") == 0)
            {
                if (command->inputs == NULL) {
                    command->inputs = redirect_info;
                }
                else 
                {
                    push_back_redirect_info(command->inputs, redirect_info);
                }
            } 
            else
            {
                if (command->outpus == NULL) {
                    command->outpus = redirect_info;
                }
                else 
                {

                    push_back_redirect_info(command->outpus, redirect_info);
                }
            }
            front_token = front_token->next;
            if (front_token == NULL)
            {
                break;
            }
        }
        else 
        {
            if (command->command_name == NULL)
            {
                command->command_name = strdup(front_token->word);
                if (command->command_name == NULL)
                {
                    return free_command(front_command);
                }
            }
            else
            {
                args = new_args(front_token->word);
                if (args == NULL)
                {
                    return free_command(front_command);
                }
                if (command->args_list == NULL)
                {
                    command->args_list = args;
                } else
                {
                    push_back_args_list(command->args_list, args);
                }
                
            }
            
        }
        front_token = front_token->next;
    }
    push_back_command(front_command, command);
    if (command->is_error)
    {
        front_command->next->is_error = true;
    }
    command = front_command->next;
    free(front_command);
    return command;
}



void print_command(t_command *command)
{
    fprintf(stdout, "\x1b[34m");
    t_redirect_info *redirect;
    t_args_list *args;
    while (command != NULL)
    {
        printf("----------------------\n");
        printf("command_name : '%s'\n", command->command_name);
        printf("input list : ");
        redirect = command->inputs;
        while (redirect != NULL)
        {
            printf("%s ", redirect->arg);
            redirect = redirect->next;
        }
        printf("\n");
        printf("output list : ");
        redirect = command->outpus;
        while (redirect != NULL)
        {
            printf("%s ", redirect->arg);
            redirect = redirect->next;
        }
        printf("\n");
        printf("args : ");
        args = command->args_list;
        while (args != NULL)
        {
            printf("%s ", args->string);
            args = args->next;
        }
        printf("\n");
        printf("next_pipe : '%d'\n", command->next_pipe);
        command = command->next;
    }
    fprintf(stdout, "\x1b[39m");   
}