/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:16:59 by dummy             #+#    #+#             */
/*   Updated: 2023/06/18 18:09:54 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LIB_H
# define MS_LIB_H

# include <stddef.h>
# include "libft.h"

# define CMD_NOT_FOUND INT_MAX
# define EXIT_NUMBER 65535
# define CONTINUE_NUMBER 65534

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

int				ft_strcmp(const char *s1, const char *s2);
char			**ft_split_use_charset(const char *str, char *charset);
int				command_echo(char **tokens);
int				command_pwd(void);
int				command_cd(const char **tokens);
int				command_env(t_env_manager *env_manager, const char **tokens);
int				command_export(t_env_manager *env_manager, const char **tokens);
int				command_unset(t_env_manager *env_manager, const char **tokens);
void			put_command_not_found(char *command);
void			strerror(int error_number);
t_env_manager	*new_env_manager(char **arg_envs);
void			env_delete(t_env_manager *env_manager, const char *key);
void			*free_env_manager(t_env_manager *env_manager);
char			*prompt(void);
t_env			*add_env(t_env_manager *env_manager, char *token);
void			free_env(t_env *env);
t_env			*new_env(char *str);
size_t			array_size(const char **array);

#endif