/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:08:40 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/25 14:52:23 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_string.h"
#include "../include/tokenize.h"
#include "libft.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char					*g_eval_char = "'\"$\\";
const size_t				g_eval_char_size = 4;

static bool	should_eval(t_token *token)
{
	size_t	i;
	size_t	j;

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

char *get_special_env(char key, t_env_manager *env_manager) 
{
	if(key == '?')
	{
		free(env_manager->string_exit_string);
		env_manager->string_exit_string = ft_itoa(env_manager->exit_status);
		return (env_manager->string_exit_string);
	}
	return NULL;
}

char	*get_env_value_ptr(char *token_string, size_t *token_index,
		t_env_manager *env_manager)
{
	char	*key;
	size_t	i;
	t_env	*env;

	if (token_string == NULL || env_manager == NULL)
		return (NULL);
	i = 0;
	if ((isdigit(token_string[0]) || (token_string[0] == '?')))
	{
		(*token_index)++;
		return get_special_env(token_string[0], env_manager);
	}
	else
	{
		key = strdup(token_string);
		if (key == NULL)
			return (NULL);
		while (!is_env_delimiter(key[i]))
			i++;
	}
	key[i] = '\0';
	*token_index += i;
	env = find_env(env_manager, key);
	free(key);
	if (env == NULL)
		return (NULL);
	return (env->value);
}

typedef struct s_eval_token_helper_args
{
	t_token					*token;
	t_env_manager			*env;
	char					quote_flag;
	size_t					i;
	t_string				*evaluated_string;
}							t_eval_token_helper_args;

bool	is_change_quote_flag(char quote_flag, char current_char)
{
	if (!(current_char == '\'' || current_char == '"'))
		return (false);
	if (current_char != quote_flag && quote_flag != '\0')
		return (false);
	return (true);
}

bool	is_expand(char quote_flag)
{
	return (quote_flag == '\0' || quote_flag == '"');
}

bool	is_add_doller(char *string)
{
	return (string[0] == '$' && is_env_delimiter(string[1]));
}

int	evaluated_token_helper(t_eval_token_helper_args *args)
{
	t_string	*push_back_ret;

	if (is_change_quote_flag(args->quote_flag, args->token->word[args->i]))
	{
		args->quote_flag ^= args->token->word[args->i];
		(args->i)++;
		return (0);
	}
	if (is_add_doller(&args->token->word[args->i]))
		push_back_ret = push_back_string(args->evaluated_string, "$");
	else if (args->token->word[args->i] == '$' && is_expand(args->quote_flag))
		push_back_ret = push_back_string(args->evaluated_string,
				get_env_value_ptr(&args->token->word[args->i + 1],
					&args->i, args->env));
	else
		push_back_ret = push_back_string_char(args->evaluated_string,
				args->token->word[args->i]);
	if (push_back_ret == NULL)
	{
		// TODO error handring
		return (-1);
	}
	(args->i)++;
	return (0);
}

t_eval_token_helper_args	*set_args(t_eval_token_helper_args *args,
									t_token *token,
									t_env_manager *env_manager)
{
	args->evaluated_string = calloc(1, sizeof(t_string));
	if (args->evaluated_string == NULL)
		return (NULL);
	if (init_string(args->evaluated_string, DEFAULT_INIT_SIZE) == NULL)
	{
		free(args->evaluated_string);
		return (NULL);
	}
	args->token = token;
	args->quote_flag = '\0';
	args->env = env_manager;
	args->i = 0;
	return (args);
}

static t_token	*evaluated_token(t_token *token, t_env_manager *env)
{
	t_token						*evaluated;
	t_eval_token_helper_args	args;

	if (set_args(&args, token, env) == NULL)
		return (NULL);
	while (args.token->word[args.i] != '\0')
	{
		if (evaluated_token_helper(&args) < 0)
		{
			// TODO error handring;
		}
	}
	evaluated = new_token(args.evaluated_string->data, 1);
	if (evaluated != NULL)
	{
		if (args.quote_flag != '\0')
			evaluated->kind = SYNTAX_ERROR;
	}
	free(args.evaluated_string->data);
	free(args.evaluated_string);
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
