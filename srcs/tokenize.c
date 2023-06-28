/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:48:39 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/28 22:43:47 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "stdlib.h"
#include "tokenize.h"
#include "parser.h"
#include "ft_xcalloc.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

t_token	*new_token(const char *word, const int kind)
{
	t_token	*token;

	if (word == NULL)
		return (NULL);
	token = ft_xcalloc(sizeof(t_token), 1);
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

void	quote_check(char *line, char *quote, size_t *i)
{
	if ((line[*i] == '\'' || line[*i] == '"'))
	{
		if (*quote == '\0')
			*quote = line[*i];
		else if (*quote == line[*i])
			*quote = '\0';
	}
}

size_t	set_next_char(char *line, char *token_string, char *quote, size_t *i)
{
	size_t	index;

	index = 0;
	if (!is_delimiter(line[*i]) || *quote != '\0')
	{
		token_string[index] = line[*i];
		(index)++;
		if (is_meta_char(line[*i]) && line[*i] == line[*i + 1])
		{
			(*i)++;
			token_string[index] = line[*i];
			(index)++;
		}
	}
	return (index);
}

size_t	set_next_token_string(char *token_string, char *line)
{
	char	quote;
	size_t	i;
	size_t	str_index;
	size_t	line_length;

	quote = '\0';
	i = 0;
	str_index = 0;
	line_length = strlen(line);
	while (i < line_length)
	{
		quote_check(line, &quote, &i);
		str_index += set_next_char(line, &token_string[str_index], &quote, &i);
		if (((str_index != 0 && strlen(token_string) != 0
					&& (is_delimiter(line[i + 1]) || is_meta_char(line[i + 1])
						|| is_meta_char(line[i]))) && quote == '\0')
			|| i == line_length - 1)
		{
			break ;
		}
		i++;
	}
	return (i + 1);
}

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

t_token_kind get_token_kind(char *token_string)
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
		bzero(token_string, strlen(token_string) + 1);
	}
	if (token_manager->last == NULL)
		add_token(token_manager, new_token("", NULL_KIND));
	evaluated = eval(token_manager, env_manager);
	free(token_string);
	free_token_manager(token_manager);
	return (evaluated);
}
