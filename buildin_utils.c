/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:18:22 by dummy             #+#    #+#             */
/*   Updated: 2023/05/11 21:47:30 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_lib.h"
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
