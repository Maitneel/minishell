/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:32:52 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/18 19:48:37 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"
#include <string.h>

int	command_cd(const char **tokens)
{
	int		ret_code;
	size_t	token_size;

	token_size = array_size(tokens);
	if (token_size < 2)
	{
		write(STDERR_FILENO, "cd: not enough arguments\n", 25);
		return (1);
	}
	if (2 < token_size)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	ret_code = chdir(tokens[1]);
	if (ret_code != 0)
	{
		write(STDERR_FILENO, "cd: ", 4);
		strerror(errno);
		return (1);
	}
	command_pwd();
	return (ret_code);
}
