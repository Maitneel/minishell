/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:29:26 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/08 00:28:43 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

bool	is_long(char *str)
{
	long	ret;
	int		sign;

	ret = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		if ((ret > (LONG_MAX - (*str - '0')) / 10) && sign == 1)
			return (false);
		if ((ret > (LONG_MAX - (*str - '0')) / 10) && sign == -1)
			return (false);
		ret = 10 * ret + (*str++ - '0');
	}
	return (*str == '\0');
}

int	command_exit(t_env_manager *env_manager, char **args)
{
	size_t	args_size;

	args_size = array_size(args);
	if (args_size == 1)
		exit(env_manager->exit_status);
	if (!is_long(args[1]))
	{
		write(STDERR_FILENO, "minishell: exit: ", 18);
		write(STDERR_FILENO, args[1], ft_strlen(args[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 29);
		exit(255);
	}
	else
	{
		if (args[2] == NULL)
			exit(ft_atoi(args[1]));
		else
		{
			if (args_size > 2)
				write(STDERR_FILENO, "minishell: exit: too many arguments\n",
					37);
			return (1);
		}
	}
}
