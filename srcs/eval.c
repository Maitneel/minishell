/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:08:40 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/19 20:17:335 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_string.h"
#include "../include/tokenize.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


const char *g_eval_char = "'\"$\\";
const	size_t	g_eval_char_size = 4;

static bool	should_eval(t_token *token)
{
	size_t			i;
	size_t			j;

	i = 0;
	while (token->word[i] != '\0')
	{
		j = 0;
		while (j < g_eval_char_size)
		{
			if (token->word[i] == g_eval_char[j])
			{
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool	is_env_delimiter(char c)
{
	return (!(isalnum(c) || c == '_'));
}

char *get_env_value_ptr(char *token_string, size_t *token_index, t_env_manager *env_manager)
{
	char *key;
	if (token_string == NULL || env_manager == NULL)
		return NULL;
	key = strdup(token_string);
	if (key == NULL)
		return NULL;
	size_t i;
	i = 0;
	if (isdigit(key[0])) {
			i++;
	}
	else {
		while (!is_env_delimiter(key[i]))
			i++;
	}
	key[i] = '\0';
    *token_index += i;
	t_env *env;
	env = find_env(env_manager, key);
	free(key);
	if (env == NULL)
		return NULL;
	return env->value;
}

static t_token	*evaluated_token(t_token *token, t_env_manager *env)
{
	t_token		*evaluated;
	t_string	evaluated_string;
	char		quote_flag;
	char		next_char_str[2];
	size_t		i;

	if (init_string(&evaluated_string, DEFAULT_INIT_SIZE) == NULL)
		return (NULL);
	quote_flag = '\0';
	next_char_str[1] = '\0';
	i = 0;
	while (token->word[i] != '\0')
	{
		if (token->word[i] == '\'' || token->word[i] == '"')
		{
			if (token->word[i] == quote_flag || quote_flag == '\0')
			{
				quote_flag ^= token->word[i];
				i++;
                continue;
			}
		}
		if (token->word[i] == '$' && is_env_delimiter(token->word[i + 1]))
		{
			if (push_back_string(&evaluated_string, "$") == NULL)
			{
				// TODO error handring
			}
		}
		else if (token->word[i] == '$' && (quote_flag == '\0'
					|| quote_flag == '"'))
		{
			if (push_back_string(&evaluated_string,
					get_env_value_ptr(&token->word[i + 1], &i, env)) == NULL)
			{
				// TODO error_handring
			}
		}
		else
		{
			next_char_str[0] = token->word[i];
			if (push_back_string(&evaluated_string, next_char_str) == NULL)
			{
				// TODO error_handring
			}
		}
		i++;
	}
	evaluated = new_token(evaluated_string.data, 1);
	free(evaluated_string.data);
	return (evaluated);
}

t_token_manager	*eval(t_token_manager *token_manager,
		t_env_manager *env_manager)
{
	t_token			*current;
	t_token_manager	*evaluated;

	evaluated = new_token_manager();
	if (evaluated == NULL)
		return (NULL);
	current = token_manager->front;
	while (current != NULL)
	{
		if (should_eval(current))
			add_token(evaluated, evaluated_token(current, env_manager));
		else
			add_token(evaluated, new_token(current->word, current->kind));
		if (evaluated->last == NULL)
		{
			free_token_manager(evaluated);
			return (NULL);
		}
		current = current->next;
	}
	current = evaluated->front;
	return (evaluated);
}
