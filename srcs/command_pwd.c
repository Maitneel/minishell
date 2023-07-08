/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:33:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/03 21:52:42 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	command_pwd(int fd)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	write(fd, buffer, ft_strlen(buffer));
	write(fd, "\n", 1);
	free(buffer);
	return (0);
}
