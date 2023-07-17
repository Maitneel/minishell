/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:32:52 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/17 17:42:34 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#include <stdio.h>

int	command_cd(char **tokens, int fd)
{
	int		ret_code;
	size_t	token_size;

	token_size = array_size(tokens);
	if (token_size < 2)
	{
		write(STDERR_FILENO, "cd: not enough arguments\n", 25);
		exit(1);
	}
	if (2 < token_size)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		exit(1);
	}
	ret_code = chdir(tokens[1]);
	if (ret_code != 0)
	{
		write(STDERR_FILENO, "cd: ", 4);
		perror(tokens[1]);
		return (1);
	}
	return (ret_code);
}
