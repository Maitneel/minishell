/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:49:12 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 17:33:29 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "env.h"
# include "ft_string.h"
# include "libft.h"
# include <stdbool.h>

typedef enum e_token_kind
{
	SYNTAX_ERROR = 1000,
	DEFAULT_KIND,
	REDIRECT_KIND,
	NULL_KIND,
}					t_token_kind;

typedef struct s_token
{
	char			*word;
	t_token_kind	kind;
	struct s_token	*next;
}					t_token;

typedef struct s_token_maneger
{
	t_token			*front;
	t_token			*last;
	size_t			size;
}					t_token_manager;

t_token				*new_token(const char *word, const int kind);
t_token_manager		*new_token_manager(void);
void				*free_token_manager(t_token_manager *token_manager);
t_token_manager		*tokenize(t_string *line, t_env_manager *env_manager);
t_token_manager		*eval(t_token_manager *token_manager,
						t_env_manager *env_manager);
char				*get_env_value_ptr(char *token_string, size_t *token_index,
						t_env_manager *env_manager);
void				add_token(t_token_manager *token_maneger, t_token *token);
void				quote_check(char *line, char *quote, size_t *i);
char				*get_special_env(char key, t_env_manager *env_manager);
bool				should_eval(t_token *token);
bool				is_env_delimiter(char c);
bool				is_change_quote_flag(char quote_flag, char current_char);
bool				is_expand(char quote_flag);
bool				is_add_doller(char *string);
char				*get_env_value_ptr(char *token_string, size_t *token_index,
						t_env_manager *env_manager);
t_token				*new_token(const char *word, const int kind);
t_token_manager		*new_token_manager(void);
void				add_token(t_token_manager *token_maneger, t_token *token);
void				*free_token_manager(t_token_manager *token_manager);
size_t				set_next_char(char *line, char *token_string, char *quote,
						size_t *i);
size_t				set_next_token_string(char *token_string, char *line);
#endif
