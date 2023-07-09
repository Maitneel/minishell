/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:34:55 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 20:43:13 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_valid_key(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (i == 0 && !(ft_isalpha(str[i]) || str[i] == '_'))
			return (false);
		if (i != 0 && !(ft_isalnum(str[i]) || str[i] == '_'))
			return (false);
		i++;
	}
	return (true && ft_strcmp(str, "=") != 0);
}

bool	valid_token(const char *str)
{	
	return (ft_strchr(str, '='));
}

int	print_invalid_error(const char *str)
{
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
	return (1);
}

int	command_export(t_env_manager *env_manager, char **tokens)
{
	size_t	i;
	int		status_code;

	if (array_size(tokens) == 1)
	{
		write(STDOUT_FILENO, "export: not enough arguments\n", 30);
		return (1);
	}
	i = 1;
	status_code = 0;
	while (i < array_size(tokens))
	{
		if (!is_valid_key(tokens[i]))
			status_code = print_invalid_error(tokens[i]);
		else if (valid_token(tokens[i]))
			add_env(env_manager, (char *)tokens[i]);
		i++;
	}
	return (status_code);
}
