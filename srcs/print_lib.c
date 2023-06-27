/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_print_lib.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:21:03 by dummy             #+#    #+#             */
/*   Updated: 2023/06/25 16:37:57 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <unistd.h>

void	put_command_not_found(char *command)
{
	write(STDERR_FILENO, "builtin not found: ", 19);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, "\n", 1);
}
