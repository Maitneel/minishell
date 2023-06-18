/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:21:03 by dummy             #+#    #+#             */
/*   Updated: 2023/05/05 16:46:37 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_lib.h"
#include <unistd.h>

void	put_command_not_found(char *command)
{
	write(STDERR_FILENO, "builtin not found: ", 19);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, "\n", 1);
}
