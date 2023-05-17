/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:49:12 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/18 04:26:03 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

#include "ft_string.h"

typedef struct s_token
{
	char			*word;
	int				kind;
	struct s_token	*next;
}					t_token;

typedef struct s_token_maneger
{
	t_token			*front;
	t_token			*last;
	size_t			size;
}					t_token_manager;

void *free_token_manager(t_token_manager *token_manager);
t_token_manager			*tokenize(t_string *line);

#endif
