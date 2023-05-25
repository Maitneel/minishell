/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:35:46 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/21 14:18:14 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_size;

	n_size = ft_strlen(needle);
	if (n_size == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (*haystack && len >= n_size)
	{
		len--;
		if (!ft_strncmp(haystack, needle, n_size))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *str = "libft-test-tokyo";
// 	int len = strlen(str);
// 	for (int i = 0; i < len; i++)
// 	{
// 		printf("ft_strnstr: %s\n", ft_strnstr(str, "libft-test-tokyo", i));
// 		printf("strnstr: %s\n", strnstr(str, "libft-test-tokyo", i));
// 	}
// }