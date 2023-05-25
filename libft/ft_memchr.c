/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:28:48 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/21 14:37:26 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*uc;
	unsigned char		target;

	target = (unsigned char)c;
	uc = s;
	while (n--)
	{
		if (*uc == target)
			return ((void *)uc);
		uc++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	printf("%s, %s\n", ft_memchr("hoge", 'o', 0), memchr("hoge", 'o', 0));
// }