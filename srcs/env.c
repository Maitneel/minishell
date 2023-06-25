/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:20:30 by dummy             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/18 17:32:29 by taksaito         ###   ########.fr       */
=======
/*   Updated: 2023/06/25 14:49:28 by dummy            ###   ########.fr       */
>>>>>>> update: $?を展開できるように変更
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <string.h>
#include <stdlib.h>

void	free_env(t_env *env)
{
	if (env == NULL)
	{
		return ;
	}
	free(env->key);
	free(env->value);
	free(env);
}

void	*free_env_manager(t_env_manager *env_manager)
{
	t_env	*next_env;
	t_env	*to_free_env;

	if (env_manager == NULL)
		return (NULL);
	next_env = env_manager->front;
	while (next_env != NULL)
	{
		to_free_env = next_env;
		next_env = to_free_env->next;
		free_env(to_free_env);
	}
	free(env_manager);
	free(env_manager->string_exit_string);
	return (NULL);
}

t_env	*new_env(char *str)
{
	t_env	*env;
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (i == 0 || str[i] == '\0')
		return (NULL);
	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->next = NULL;
	env->key = ft_substr(str, 0, i);
	env->value = ft_substr(str, i + 1, strlen(str) - 1);
	return (env);
}

t_env_manager	*new_env_manager(char **arg_envs)
{
	t_env_manager	*env_manager;
	size_t			i;

	env_manager = malloc(sizeof(t_env_manager));
	if (env_manager == NULL)
		return (NULL);
	env_manager->string_exit_string = NULL;
	env_manager->exit_status = 0;
	env_manager->front = new_env(arg_envs[0]);
	env_manager->last = env_manager->front;
	env_manager->size = 1;
	if (env_manager->front == NULL)
		return (env_manager);
	env_manager->size = 1;
	i = 1;
	while (arg_envs[i] != NULL)
	{
		if (env_manager->last == NULL)
			return (free_env_manager(env_manager));
		env_manager->last->next = new_env(arg_envs[i]);
		if (env_manager->last->next == NULL)
			return (free_env_manager(env_manager));
		env_manager->last = env_manager->last->next;
		env_manager->size++;
		i++;
	}
	return (env_manager);
}

/*
int	command_env(t_env_manager *env_manager, const char **tokens)
{
	size_t	i;
	t_env	*next;

	i = 0;
	if (array_size(tokens) != 1)
	{
		write(STDERR_FILENO, "env: too many arguments\n", 24);
	}
	next = env_manager->front;
	while (next != NULL)
	{
		write(STDOUT_FILENO, next->key, ft_strlen(next->key));
		write(STDERR_FILENO, "=", 1);
		write(STDOUT_FILENO, next->value, ft_strlen(next->value));
		write(STDOUT_FILENO, "\n", 1);
		next = next->next;
		i++;
	}
	return (0);
}
// */
