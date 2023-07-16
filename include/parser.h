/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:58:09 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/16 21:57:05 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenize.h"
# include <stdbool.h>

typedef enum e_redirect_enum
{
	REDIRECT_IN = 0,
	REDIRECT_HEAR_DOC,
	EXPANDED_HEREDOC,
	REDIRECT_OUT_OVERWRITE,
	REDIRECT_OUT_POST
}							t_redirect_enum;

typedef enum e_return_status
{
	SUCCESS = 3000,
	TO_RETURN,
	TO_BREAK
}							t_return_status;

typedef struct s_redirect_info
{
	char					*arg;
	t_redirect_enum			kind;
	struct s_redirect_info	*next;
}							t_redirect_info;

typedef struct s_args_list
{
	char					*string;
	struct s_args_list		*next;
}							t_args_list;

typedef struct s_command
{
	bool					is_error;
	bool					is_heredoc_error;
	char					*command_name;
	char					**args;
	t_args_list				*args_list;
	t_redirect_info			*inputs;
	t_redirect_info			*outpus;
	bool					next_pipe;
	struct s_command		*next;
}							t_command;

void						*free_command(t_command *command);
t_command					*parse(t_token_manager *token_manager,
								t_env_manager *env_manager);
void						print_command(t_command *command);
bool						is_in_redirect_word(char *string);
bool						is_out_redirect_word(char *string);
bool						is_redirect_word(char *string);
bool						is_redirect_word(char *string);
void						*free_redirect_info(t_redirect_info *front);
t_redirect_info				*new_redirect_info(void);
void						push_back_redirect_info(t_redirect_info **front,
								t_redirect_info *node);
void						*free_args_list(t_args_list *front);
void						push_back_args_list(t_args_list **front,
								t_args_list *node);
t_args_list					*new_args_list(char *string);
bool						add_redirect(t_command *command,
								t_token *front_token,
								t_env_manager *env_manager);
void						*free_command(t_command *command);
t_command					*new_command(void);
void						push_back_command(t_command **front,
								t_command *command);
bool						add_command_name_or_args(t_command *command,
								t_token *front_token);
int							expand_here_doc(t_command *command,
								t_env_manager *env_manager);
void						set_redirect_kind(char *token_word,
								t_redirect_info *redirect_info);
t_command					*syntax_error_in_front(t_token *f_token,
								t_command *cmd, t_env_manager *env_manager);

#endif
