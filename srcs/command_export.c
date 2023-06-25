/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:34:55 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/25 17:02:05 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	valid_token(const char *str)
{
	return (ft_strchr(str, '='));
}

int	command_export(t_env_manager *env_manager, char **tokens)
{
	size_t	i;

	if (array_size(tokens) == 1)
	{
		write(STDOUT_FILENO, "export: not enough arguments\n", 30);
		return (1);
	}
	i = 1;
	while (i < array_size(tokens))
	{
		if (!valid_token(tokens[i]))
			write(STDOUT_FILENO, "export: error\n", 14);
		else
		{
			if (add_env(env_manager, (char *)tokens[i]) == NULL)
				write(STDOUT_FILENO, "export: error\n", 14);
		}
		i++;
	}
	return (0);
}
