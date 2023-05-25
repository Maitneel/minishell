/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:15:35 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/16 00:04:43 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*dest;

	dest = (unsigned char *)b;
	i = len;
	while (i--)
		dest[i] = (unsigned char)c;
	return (b);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	memset(NULL, 's', 1); // segmentation fault
// }