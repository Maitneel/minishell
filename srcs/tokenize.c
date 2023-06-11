/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:48:39 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/11 16:03:18 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "stdlib.h"
#include "tokenize.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

t_token	*new_token(const char *word, const int kind)
{
	t_token	*token;

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

t_token_manager	*new_token_manager(void)
{
	t_token_manager	*new;

	new = malloc(sizeof(t_token_manager));
	if (new == NULL)
	{
		return (NULL);
	}
	new->front = NULL;
	new->last = NULL;
	new->size = 0;
	return (new);
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

// 区切り文字判定
// この関数をいじればtokenizeの区切りを変えられる
const char		*g_delimiter = " \t\n\f\r";
const size_t	g_delimiter_size = 5;

bool	is_delimiter(char c)
{
	size_t	i;

	i = 0;
	while (i < g_delimiter_size)
	{
		if (c == g_delimiter[i])
		{
			return (true);
		}
		i++;
	}
	return (false);
}

const char		*g_meta_char = "<>|&";
const size_t	g_meta_char_size = 4;

bool	is_meta_char(char c)
{
	size_t	i;

	i = 0;
	while (i < g_meta_char_size)
	{
		if (c == g_meta_char[i])
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void quote_check(t_string *line, char *token_string, char *quote, size_t *i, size_t *str_index)
{
    if ((line->data[*i] == '\'' || line->data[*i] == '"'))
		{
			if (*quote == '\0')
				*quote = line->data[*i];
			else if (*quote == line->data[*i])
				*quote = '\0';
		}
		if (!is_delimiter(line->data[*i]) || *quote != '\0')
		{
			token_string[*str_index] = line->data[*i];
			(*str_index)++;
			if (is_meta_char(line->data[*i]) && line->data[*i] == line->data[*i + 1])
			{
				(*i)++;
				token_string[*str_index] = line->data[*i];
				(*str_index)++;
			}
		}
}

t_token_manager	*tokenize(t_string *line, t_env_manager *env_manager)
{
	t_token_manager	*token_manager;
	char			*token_string;
	size_t			i;
	size_t			str_index;
	t_token			*token;
	char			quote;
	t_token_manager	*evaluated;

	token_manager = new_token_manager();
	if (token_manager == NULL)
		return (NULL);
	// TODO 適切な長さに変更する
	token_string = calloc(sizeof(char), line->length + 10);
	if (token_string == NULL)
		return (free_token_manager(token_manager));
	quote = '\0';
	str_index = 0;
	i = 0;
	while (i < line->length)
	{
        // quote_check(line, token_string, &quote, &i, &str_index);
		if ((line->data[i] == '\'' || line->data[i] == '"'))
		{
			if (quote == '\0')
				quote = line->data[i];
			else if (quote == line->data[i])
				quote = '\0';
		}
		if (!is_delimiter(line->data[i]) || quote != '\0')
		{
			token_string[str_index] = line->data[i];
			str_index++;
			if (is_meta_char(line->data[i]) && line->data[i] == line->data[i + 1])
			{
				i++;
				token_string[str_index] = line->data[i];
				str_index++;
			}
		}
		if (((str_index != 0 && (is_delimiter(line->data[i + 1]) || is_meta_char(line->data[i + 1]) || is_meta_char(line->data[i]))) && quote == '\0' ) || i == line->length - 1) 
		{
			if (strlen(token_string) == 0)
			{
				// 要検討 ここbreakでもいい？ //
				// 1つ上のifの条件に追加でもいいかも //
				i++;
				continue ;
			}
			token = new_token(token_string, DEFAULT_KIND);
			if (token == NULL)
				return (free_token_manager(token_manager));
			if (token_manager->last == NULL)
			{
				token_manager->front = token;
				token_manager->last = token;
			}
			else
			{
				token_manager->last->next = token;
				token_manager->last = token;
			}
			token_manager->size++;
			bzero(token_string, str_index + 1);
			str_index = 0;
		}
		i++;
	}
	if (token_manager->last == NULL)
	{
		token_manager->front = new_token("", NULL_KIND);
		token_manager->last = token_manager->front;
	}
	evaluated = eval(token_manager, env_manager);
	free(token_string);
	free_token_manager(token_manager);
	return (evaluated);
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
	return ;
}
