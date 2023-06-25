/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:34:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/22 20:29:33 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	command_echo(char **tokens)
{
	size_t	i;
	bool	is_print_nl;

	is_print_nl = true;
	i = 1;
	if (ft_strcmp(tokens[1], "-n") == 0)
	{
		i++;
		is_print_nl = false;
	}
	while (tokens[i] != NULL)
	{
		write(STDOUT_FILENO, tokens[i], ft_strlen(tokens[i]));
		i++;
		if (tokens[i] != NULL)
		{
			write(STDOUT_FILENO, " ", 1);
		}
	}
	if (is_print_nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
