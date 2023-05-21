/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:08:16 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/21 11:23:16 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static size_t	get_split_size(const char *str, char c)
{
	size_t	cnt;
	size_t	size;

	size = 0;
	while (*str)
	{
		cnt = 0;
		while (str[cnt] && str[cnt] != c)
			cnt++;
		if (cnt > 0)
		{
			size++;
			str = str + cnt;
		}
		else
			str++;
	}
	return (size);
}

static void	*free_all_ptr(char **p)
{
	size_t	i;

	i = 0;
	while (p[i] != NULL)
	{
		free(p[i]);
		p[i] = NULL;
		i++;
	}
	free(p);
	return (NULL);
}

static char	**split(char **ret, const char *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	while (*s)
	{
		cnt = 0;
		while (s[cnt] && s[cnt] != c)
			cnt++;
		if (cnt > 0)
		{
			ret[i] = calloc(sizeof(char), (cnt + 1));
			if (ret[i] == NULL)
				return (free_all_ptr(ret));
			strlcpy(ret[i], s, cnt + 1);
			i++;
			s += cnt;
		}
		else
			s++;
	}
	ret[i] = (NULL);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	ret_size;

	if (s == NULL)
		return (NULL);
	ret_size = get_split_size(s, c);
	ret = (char **)malloc(sizeof(char *) * (ret_size + 1));
	if (ret == NULL)
		return (NULL);
	ret = split(ret, s, c);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

// #include <stdio.h>
// void	print_arr(char **p)
// {
// 	while (*p != NULL)
// 	{
// 		printf("%s\n", *p);
// 		p++;
// 	}
// }

// int	main(void)
// {
// 	char	**splited;

// 	splited = ft_split("hello,world,42,tokyo", ',');
// 	print_arr(splited);
// 	// ft_split("hello world 42 tokyo", ' ');
// 	// ft_split(",,,hello,,,world,,,42,,,tokyo,,,,", ',');
// 	// // expected2[] = {"hello,world,42,tokyo", NULL};
// 	// ft_split("hello,world,42,tokyo", ' ');
// 	// ft_split("hello,world,42,tokyo", '{');
// 	// // expected3[] = {NULL};
// 	// ft_split("", ',');
// }
