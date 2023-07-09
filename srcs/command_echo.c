/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:34:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 17:17:07 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	command_echo(char **tokens, int fd)
{
	size_t	i;
	bool	is_print_nl;

	is_print_nl = true;
	i = 1;
	if (tokens[i] != NULL && ft_strcmp(tokens[i], "-n") == 0)
	{
		i++;
		is_print_nl = false;
	}
	while (tokens[i] != NULL)
	{
		write(fd, tokens[i], ft_strlen(tokens[i]));
		i++;
		if (tokens[i] != NULL)
		{
			write(fd, " ", 1);
		}
	}
	if (is_print_nl)
		write(fd, "\n", 1);
	return (0);
}
