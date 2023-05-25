/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:06:26 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/22 13:23:47 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	sub_size;
	size_t	s_size;

	if (s == NULL)
		return (NULL);
	sub_size = len;
	s_size = ft_strlen(s);
	if (s_size <= start)
		return (ft_calloc(sizeof(char), 1));
	else if (len == 0)
		return (ft_calloc(sizeof(char), 1));
	else if (len >= s_size - start)
		sub_size = s_size - start;
	ret = ft_calloc(sizeof(char), (sub_size + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, &s[start], sub_size + 1);
	return (ret);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *s = "libft-test-tokyo";
// 	printf("%s\n", ft_substr(s, 0, 16));
// 	printf("%s\n", ft_substr(s, 20, 5));
// }