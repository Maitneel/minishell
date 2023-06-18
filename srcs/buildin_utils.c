/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:18:22 by dummy             #+#    #+#             */
/*   Updated: 2023/06/18 19:50:02 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <unistd.h>

size_t	array_size(const char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}
