/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:18:31 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/21 14:10:27 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p;
	char		target;

	target = (char)(c);
	p = s;
	while (*p != '\0' && *p != target)
		p++;
	if (*p == '\0' && target != '\0')
		return (NULL);
	return ((char *)p);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	strstr(NULL, 'c'); // segmentation fault
// }