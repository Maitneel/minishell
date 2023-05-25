/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 01:46:49 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/20 01:18:59 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = dst;
	sp = src;
	if (dp < sp)
	{
		while (len--)
			*dp++ = *sp++;
	}
	else if (dp > sp)
	{
		dp = dst + len - 1;
		sp = src + len - 1;
		while (len--)
			*dp-- = *sp--;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *dest = malloc(11);
// 	for (int i = 0; i < 10; i++)
// 		dest[i] = i + '0';
// 	dest[10] = '\0';
// 	ft_memmove(dest, dest + 4, 4);
// 	printf("%s\n", dest);

// 	printf("%s\n", ft_memmove(NULL, NULL, 4));
// 	printf("%s\n", memmove(NULL, NULL, 4));
// }