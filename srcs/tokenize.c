/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:48:39 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/14 16:13:13 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "stdlib.h"
#include <string.h>

static t_token *new_token(const char *word, const int kind)
{
	t_token *token;

	if (word == NULL)
		return (NULL);
	token = calloc(sizeof(t_token), 1);
	if (token == NULL)
		return (NULL);
	token->word = strdup(word);
	token->kind = kind;
	token->next = NULL;
	if (token->word == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_tokenize	*tokenize(char *line)
{
	t_tokenize *tokenzie;
	tokenzie = calloc(sizeof(t_tokenize), 1);
	tokenzie->tokens = new_token("cd", 1);
	tokenzie->tokens->next = new_token("hoge", 1);
	(void)line;
	return (tokenzie);
}

