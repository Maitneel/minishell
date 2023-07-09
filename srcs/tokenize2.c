/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:25:22 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:25:27 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "ft_xcalloc.h"
#include <stdlib.h>


t_token	*new_token(const char *word, const int kind)
{
	t_token	*token;

	if (word == NULL)
		return (NULL);
	token = ft_xcalloc(sizeof(t_token), 1);
	if (token == NULL)
		return (NULL);
	token->word = ft_strdup(word);
	token->kind = kind;
	token->next = NULL;
	if (token->word == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_token_manager	*new_token_manager(void)
{
	t_token_manager	*new;

	new = ft_xcalloc(1, sizeof(t_token_manager));
	if (new == NULL)
	{
		return (NULL);
	}
	new->front = NULL;
	new->last = NULL;
	new->size = 0;
	return (new);
}

void	add_token(t_token_manager *token_maneger, t_token *token)
{
	if (token_maneger == NULL)
	{
		return ;
	}
	if (token_maneger->last == NULL)
	{
		token_maneger->front = token;
		token_maneger->last = token;
	}
	else
	{
		token_maneger->last->next = token;
		token_maneger->last = token;
	}
	token_maneger->size++;
	return ;
}

void	*free_token_manager(t_token_manager *token_manager)
{
	t_token	*next;
	t_token	*current;

	if (token_manager == NULL)
		return (NULL);
	current = token_manager->front;
	while (current != NULL)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	free(token_manager);
	return (NULL);
}
