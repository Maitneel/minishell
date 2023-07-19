/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:32:52 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/17 18:17:26 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include <stdio.h>

static char	*get_destination_dir(char **tokens, t_env_manager *env_manager)
{
	t_env	*home_env;
	char	*destination_dir;
	size_t	token_size;

	token_size = array_size(tokens);
	if (token_size < 2)
	{
		home_env = find_env(env_manager, "HOME");
		if (home_env == NULL)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
			return (NULL);
		}
		destination_dir = home_env->value;
	}
	else
		destination_dir = tokens[1];
	return (destination_dir);
}

int	command_cd(t_env_manager *env_manager, char **tokens)
{
	int		ret_code;
	char	*destination_dir;

	destination_dir = get_destination_dir(tokens, env_manager);
	if (destination_dir == NULL)
		return (1);
	ret_code = chdir(destination_dir);
	if (ret_code != 0)
	{
		write(STDERR_FILENO, "cd: ", 4);
		perror(destination_dir);
		return (1);
	}
	return (ret_code);
}
