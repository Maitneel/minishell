/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:26:58 by dummy             #+#    #+#             */
/*   Updated: 2023/06/25 16:26:59 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_env_manager
{
	struct s_env	*front;
	struct s_env	*last;
	size_t			size;
}					t_env_manager;

/* ----------------- env.c ----------------- */
void				free_env(t_env *env);
void				*free_env_manager(t_env_manager *env_manager);
t_env				*new_env(char *str);
t_env_manager		*new_env_manager(char **arg_envs);
/* ----------------- env2.c ----------------- */
t_env				*find_before_env(t_env_manager *env_manager,
						const char *key);
t_env				*find_env(t_env_manager *env_manager, const char *key);
t_env				*add_env(t_env_manager *env_manager, char *token);
void				env_delete(t_env_manager *env_manager, const char *key);
char				**make_env_ptr(t_env_manager *env_manager);

#endif