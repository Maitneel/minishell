/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:37:49 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/21 19:54:58 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (count != 0 && size > SIZE_T_MAX / count)
	{
		errno = ENOMEM;
		return (NULL);
	}
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	res = malloc(count * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	unsigned char *p;
// 	// ft_calloc(INT32_MAX, INT32_MAX);
// 	// printf("%s", strerror(errno));
// 	p = calloc(0, 0);
// 	printf("%p", p[1]);
// }