/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:29:48 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/20 23:16:03 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = dst;
	sp = src;
	if (dp < sp)
	{
		while (n--)
			*dp++ = *sp++;
	}
	else if (dp > sp)
	{
		dp = dst + n - 1;
		sp = src + n - 1;
		while (n--)
			*dp-- = *sp--;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char *dst;
// 	dst = malloc(10);
// 	memcpy(dst, "hoge", 4);
// 	printf("%s", dst);

// 	ft_memcpy(NULL, "hoge", 4);
// 	// memcpy(NULL, "hoge", 4); // segmentation fault
// }