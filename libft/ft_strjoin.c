/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:06:55 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/11 20:25:50 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	concat_len;
	char	*concat_str;

	if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	if (s2 == NULL)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	concat_len = s1_len + s2_len;
	concat_str = malloc(concat_len + 1);
	if (concat_str == NULL)
		return (NULL);
	ft_bzero(concat_str, concat_len + 1);
	if (s1 != NULL)
		ft_strlcat(concat_str, s1, s1_len + 1);
	if (s2 != NULL)
		ft_strlcat(concat_str + s1_len, s2, s2_len + 1);
	return (concat_str);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n", ft_strjoin("hoge", "aizu"));
// 	return (0);
// }
