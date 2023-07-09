/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:31:12 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:25:27 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "env.h"
#include "ft_xcalloc.h"
#include "libft.h"
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
	if (ft_strcmp(env->key, key) == 0)
	{
		return (env);
	}
	while (env->next != NULL)
	{
		before_env = env;
		env = env->next;
		if (ft_strcmp(env->key, key) == 0)
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
		if (ft_strcmp(env->key, key) == 0)
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
	if (before_env == env_manager->front && ft_strcmp(before_env->key, key) == 0)
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

// size_t get_env_list_size(t_env *env)
// {
// 	size_t cnt;
// 	t_env *current;

// 	current = env;
// 	cnt = 0;
// 	while (current != NULL)
// 	{
// 		current = env->next;
// 		cnt++;
// 	}
// 	return (cnt);
// }

char	*get_raw_string(t_env *env)
{
	char	*appended_equal;
	char	*raw_string;

	appended_equal = ft_strjoin(env->key, "=");
	if (appended_equal == NULL)
		return (NULL);
	raw_string = ft_strjoin(appended_equal, env->value);
	free(appended_equal);
	return (raw_string);
}

// void *free_env_array(char **env_arra)
// {
// 	t_env *current;
// 	t_env *next;

// 	current = env;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current);
// 		current = next;
// 	}
// 	return (NULL);
// }
