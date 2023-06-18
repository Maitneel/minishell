/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:34:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/11 21:37:57 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_lib.h"

int	command_echo(char **tokens)
{
	size_t	i;

	i = 1;
	while (tokens[i] != NULL)
	{
		write(STDOUT_FILENO, tokens[i], ft_strlen(tokens[i]));
		i++;
		if (tokens[i] != NULL)
		{
			write(STDOUT_FILENO, " ", 1);
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
