/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:20:18 by dummy             #+#    #+#             */
/*   Updated: 2023/07/17 17:45:02 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "env.h"
# include "libft.h"
# include <stddef.h>

# define CMD_NOT_FOUND INT_MAX
# define EXIT_NUMBER 65535
# define CONTINUE_NUMBER 65534

int		ft_strcmp(const char *s1, const char *s2);
int		command_echo(char **tokens, int fd);
int		command_pwd(int fd);
int		command_cd(char **tokens);
int		command_env(t_env_manager *env_manager, char **tokens, int fd);
int		command_export(t_env_manager *env_manager, char **tokens);
int		command_unset(t_env_manager *env_manager, char **tokens);
int		command_exit(t_env_manager *env_manager, char **tokens);
void	*free_env_manager(t_env_manager *env_manager);
t_env	*add_env(t_env_manager *env_manager, char *token);
void	free_env(t_env *env);
t_env	*new_env(char *str);
size_t	array_size(char **array);

#endif