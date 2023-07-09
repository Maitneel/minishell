/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:20:30 by dummy             #+#    #+#             */
/*   Updated: 2023/07/07 23:55:09 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "ft_xcalloc.h"
#include "builtin.h"
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
	free(env_manager->string_exit_status);
	free(env_manager);
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
	env = ft_xcalloc(sizeof(t_env), 1);
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
	t_env			*env;
	size_t			i;

	env_manager = ft_xcalloc(1, sizeof(t_env_manager));
	env_manager->last = env_manager->front;
	env_manager->size = 0;
	i = 0;
	while (arg_envs[i] != NULL)
	{
		env = new_env(arg_envs[i]);
		if (env_manager->front == NULL)
		{
			env_manager->front = env;
			env_manager->last = env;
		}
		else
		{
			env_manager->last->next = env;
			env_manager->last = env;
		}
		env_manager->size++;
		i++;
	}
	return (env_manager);
}

int	command_env(t_env_manager *env_manager, char **tokens, int fd)
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
		write(fd, next->key, ft_strlen(next->key));
		write(fd, "=", 1);
		write(fd, next->value, ft_strlen(next->value));
		write(fd, "\n", 1);
		next = next->next;
		i++;
	}
	return (0);
}
