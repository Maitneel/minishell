/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:33:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/17 17:40:18 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

int	command_pwd(int fd)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer == NULL )
	{
		perror("minishell: pwd");
		return 0;
	}
	write(fd, buffer, ft_strlen(buffer));
	write(fd, "\n", 1);
	free(buffer);
	return (0);
}
