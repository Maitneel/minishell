/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:33:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/03 21:02:59 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	command_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	return (0);
}
