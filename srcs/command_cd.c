/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:32:52 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/03 21:53:18 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <string.h>

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
		strerror(errno);
		exit(1);
	}
	command_pwd(fd);
	return (ret_code);
}
