/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:08:40 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 16:28:06 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_string.h"
#include "../include/tokenize.h"
#include "libft.h"
#include "ft_xcalloc.h"
#include "print_lib.h"
#include <ctype.h>
#include <stdbool.h>

#include <stdlib.h>


char	*get_special_env(char key, t_env_manager *env_manager)
{
	if (key == '?')
	{
		free(env_manager->string_exit_status);
		env_manager->string_exit_status = ft_itoa(env_manager->exit_status);
		return (env_manager->string_exit_status);
	}
	return (NULL);
}

typedef struct s_eval_token_helper_args
{
	t_token					*token;
	t_env_manager			*env;
	char					quote_flag;
	size_t					i;
	t_string				*evaluated_string;
}							t_eval_token_helper_args;

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
	args->evaluated_string = ft_xcalloc(1, sizeof(t_string));
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
		{
			print_unclosed_quote();
			evaluated->kind = SYNTAX_ERROR;
		}
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
