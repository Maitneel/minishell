/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:31:12 by dummy             #+#    #+#             */
/*   Updated: 2023/05/25 11:48:30 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <string.h>
#include <stdlib.h>

t_env	*find_before_env(t_env_manager *env_manager, const char *key)
{
	t_env	*before_env;
	t_env	*env;

	if (env_manager == NULL)
	{
		return (NULL);
	}
	env = env_manager->front;
	if (env == NULL)
		return (NULL);
	if (strcmp(env->key, key) == 0)
	{
		return (env);
	}
	while (env->next != NULL)
	{
		before_env = env;
		env = env->next;
		if (strcmp(env->key, key) == 0)
		{
			return (before_env);
		}
	}
	return (NULL);
}

t_env	*find_env(t_env_manager *env_manager, const char *key)
{
	t_env	*env;

	env = env_manager->front;
	while (env != NULL)
	{
		if (strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*add_env(t_env_manager *env_manager, char *token)
{
	t_env	*env;
	t_env	*exist;

	env = new_env(token);
	if (env == NULL)
		return (NULL);
	exist = find_env(env_manager, env->key);
	if (exist == NULL)
	{
		if (env_manager->front == NULL)
			env_manager->front = env;
		else
			env_manager->last->next = env;
		env_manager->last = env;
		return (env);
	}
	else
	{
		free(exist->value);
		exist->value = env->value;
		env->value = NULL;
		free_env(env);
		return (exist);
	}
}

void	env_delete(t_env_manager *env_manager, const char *key)
{
	t_env	*before_env;
	t_env	*next_env;

	before_env = find_before_env(env_manager, key);
	if (before_env == NULL)
	{
		return ;
	}
	if (before_env == env_manager->front && strcmp(before_env->key, key
		) == 0)
	{
		env_manager->front = before_env->next;
		free_env(before_env);
	}
	else
	{
		next_env = before_env->next->next;
		free_env(before_env->next);
		before_env->next = next_env;
		if (next_env == NULL)
		{
			env_manager->last = before_env;
		}
	}
}
