/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:07:57 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/21 14:20:01 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

static size_t	head_count(const char *p, const char *set)
{
	size_t	cnt;

	cnt = 0;
	while (*p && is_set(set, *p))
	{
		cnt++;
		p++;
	}
	return (cnt);
}

static size_t	tail_count(const char *p, const char *set)
{
	size_t	cnt;
	size_t	i;

	i = ft_strlen(p) - 1;
	cnt = 0;
	while (is_set(set, p[i]))
	{
		cnt++;
		i--;
	}
	return (cnt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	head_cnt;
	size_t	tail_cnt;
	size_t	s_size;
	size_t	trim_size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	head_cnt = head_count(s1, set);
	tail_cnt = tail_count(s1, set);
	s_size = ft_strlen(s1);
	trim_size = s_size - head_cnt - tail_cnt;
	if (s_size == head_cnt && s_size == tail_cnt)
		return (ft_calloc(sizeof(char), 1));
	ret = ft_calloc(sizeof(char), trim_size + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcat(ret, &s1[head_cnt], (trim_size + 1));
	return (ret);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n", ft_strtrim("_aizu+", "_+"));
// 	// printf("%s\n", ft_strtrim("_aizu+", ""));
// 	// printf("%s\n", ft_strtrim("_aizu+", NULL));
// }