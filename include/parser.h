/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:58:09 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/21 13:26:334 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenize.h"
# include <stdbool.h>

# define REDIRECT_IN 1
# define REDIRECT_HEAR_DOC 2
# define REDIRECT_OUT_OVERWRITE 3
# define REDIRECT_OUT_POST 4

// typedef struct s_command
// {
//     char *name;
//     int kind; // redirect, builtin, 
//     char **args;
//     char *output;
//     bool next_pipe;
//     struct s_command *next;
// }   t_command;

typedef struct s_redirect_info
{
    char *arg;
    int kind;
    struct s_redirect_info *next;
}   t_redirect_info;

typedef struct s_args_list
{
    char *string;
    struct s_args_list *next;
} t_args_list;

typedef struct s_command
{
    // int kind; // redirect, builtin, 

    bool is_error;
    char *command_name;
    char **args;
    t_args_list *args_list;
    t_redirect_info *inputs;
    t_redirect_info *outpus;
    bool next_pipe;
    struct s_command *next;
}   t_command;
/*
> Makefile cat > hoge.txt < ./include/env.h 
// [{
    "input_file": "./include/env.h",
    "command": "cat"
    "output_file": "hoge.txt"
}]
*/

void *free_command(t_command *command);
t_command   *parse(t_token_manager *token_manager);
void print_command(t_command *command);

#endif
