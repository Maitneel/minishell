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

#include "tokenize.h"
#include <stdbool.h>

static bool should_eval(t_token *token)
{
    (void)token;
    return true;
}

static t_token *evaluated_token(t_token *token, t_env_manager *env)
{
    (void)token;
    (void)env;
    return NULL;
}

t_token_manager *eval(t_token_manager *token_manager, t_env_manager *env_manager)
{
    t_token *current;
    t_token_manager *evaluated;

	evaluated = new_token_manager();
	if (evaluated == NULL)
		return NULL;
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
			return NULL;
		}
        current = current->next;
    }
    return evaluated;
}
