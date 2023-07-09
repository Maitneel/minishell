/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:18:22 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:36:30 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stddef.h>
#include <stdlib.h>

#include <unistd.h>

size_t	array_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}
