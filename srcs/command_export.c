/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:34:55 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/18 19:19:03 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

bool	valid_token(const char *str)
{
	return (ft_strchr(str, '='));
}

int	command_export(t_env_manager *env_manager, const char **tokens)
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
