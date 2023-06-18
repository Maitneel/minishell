/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:20:18 by dummy             #+#    #+#             */
/*   Updated: 2023/06/18 19:10:14 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILDIN_H
# define BUILDIN_H

# include <stddef.h>
# include "libft.h"
# include "env.h"

# define CMD_NOT_FOUND INT_MAX
# define EXIT_NUMBER 65535
# define CONTINUE_NUMBER 65534

int				ft_strcmp(const char *s1, const char *s2);
int				command_echo(char **tokens);
int				command_pwd(void);
int				command_cd(const char **tokens);
int				command_env(t_env_manager *env_manager, const char **tokens);
int				command_export(t_env_manager *env_manager, const char **tokens);
int				command_unset(t_env_manager *env_manager, const char **tokens);
void			put_command_not_found(char *command);
void			env_delete(t_env_manager *env_manager, const char *key);
void			*free_env_manager(t_env_manager *env_manager);
t_env			*add_env(t_env_manager *env_manager, char *token);
void			free_env(t_env *env);
t_env			*new_env(char *str);
size_t			array_size(const char **array);

#endif