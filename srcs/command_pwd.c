/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:33:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/18 19:19:07 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	command_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	return (0);
}
