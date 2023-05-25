/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:08:59 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/21 14:19:35 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = f((unsigned int)i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

// #include <stdio.h>
// char	f(unsigned int i, char c)
// {
// 	(void)i;
// 	return (c + i);
// }

// int	main(void)
// {
// 	printf("%s\n", ft_strmapi("aizu", f));
// 	return (0);
// }