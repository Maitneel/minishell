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

typedef struct s_command
{
    char *name;
    int kind; // redirect, builtin, 
    char **args;
    char *output;
    bool next_pipe;
    struct s_command *next;
}   t_command;

t_command   *parse(t_token_manager *token_manager);

#endif
