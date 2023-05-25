/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:46:22 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/13 21:49:00 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*res;
	unsigned char	target;

	res = NULL;
	target = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == target)
			res = (char *)s;
		s++;
	}
	if (*s == target)
		res = (char *)s;
	return (res);
}
