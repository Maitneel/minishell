/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:48:39 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 16:06:24 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_xcalloc.h"
#include "parser.h"
#include "stdlib.h"
#include "tokenize.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool	tokenize_setup(t_token_manager **token_manager, char **token_string,
		size_t *i, t_string *line)
{
	*token_manager = new_token_manager();
	if (*token_manager == NULL)
		return (true);
	*token_string = ft_xcalloc(sizeof(char), line->length + 1);
	if (*token_string == NULL)
	{
		free_token_manager(*token_manager);
		return (true);
	}
	*i = 0;
	return (false);
}

t_token_kind	get_token_kind(char *token_string)
{
	if (token_string == NULL)
		return (NULL_KIND);
	if (is_redirect_word(token_string))
		return (REDIRECT_KIND);
	return (DEFAULT_KIND);
}

t_token_manager	*tokenize(t_string *line, t_env_manager *env_manager)
{
	t_token_manager	*token_manager;
	char			*token_string;
	size_t			i;
	t_token			*token;
	t_token_manager	*evaluated;

	if (tokenize_setup(&token_manager, &token_string, &i, line) == true)
		return (NULL);
	while (i < line->length)
	{
		i += set_next_token_string(token_string, &line->data[i]);
		if (token_string[0] == '\0')
			continue ;
		token = new_token(token_string, get_token_kind(token_string));
		if (token == NULL)
			return (free_token_manager(token_manager));
		add_token(token_manager, token);
		bzero(token_string, ft_strlen(token_string) + 1);
	}
	if (token_manager->last == NULL)
		add_token(token_manager, new_token("", NULL_KIND));
	evaluated = eval(token_manager, env_manager);
	free(token_string);
	free_token_manager(token_manager);
	return (evaluated);
}
