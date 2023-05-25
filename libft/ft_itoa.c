/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:08:35 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/18 20:13:53 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	get_digit(int n)
{
	if (n < 0)
		return ((n % 10) * -1 + '0');
	return ((n % 10) + '0');
}

static char	*assign_zero_or_minus(char *s, int n)
{
	if (n < 0)
		s[0] = '-';
	else if (n == 0)
		s[0] = '0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*ret;
	size_t	digits;
	size_t	i;

	digits = get_digits(n);
	ret = malloc(sizeof(char) * (digits + 1));
	if (ret == NULL)
		return (NULL);
	i = 1;
	ret = assign_zero_or_minus(ret, n);
	while (n)
	{
		ret[digits - i] = get_digit(n);
		n /= 10;
		i++;
	}
	ret[digits] = '\0';
	return (ret);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s\n", ft_itoa(-100));
// 	printf("%s\n", ft_itoa(-0));
// 	printf("%s\n", ft_itoa(-100));
// 	printf("%s\n", ft_itoa(100));
// }