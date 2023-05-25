/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 00:37:05 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/22 14:14:38 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

static const char	*ignore_space(const char *str)
{
	while (*str && is_space(*str))
		str++;
	return (str);
}

static const char	*calc_sign(const char *str, int *sign)
{
	*sign = 1;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	return (str);
}

static int	get_integer(const char *str, int sign)
{
	long	ret;

	ret = 0;
	while (*str && ft_isdigit(*str))
	{
		if ((ret > (LONG_MAX - (*str - '0')) / 10) && sign == 1)
			return ((int)LONG_MAX);
		if ((ret > (LONG_MAX - (*str - '0')) / 10) && sign == -1)
			return ((int)LONG_MIN);
		ret = 10 * ret + (*str++ - '0');
	}
	return (sign * ret);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	sum;

	str = ignore_space(str);
	str = calc_sign(str, &sign);
	sum = get_integer(str, sign);
	return (sum);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d\n", ft_atoi("0"));
// 	printf("%d\n", ft_atoi("-0"));
// 	printf("%d\n", ft_atoi("-100"));
// 	printf("%d\n", ft_atoi("-100"));
// 	printf("%d\n", ft_atoi("-1"));
// 	printf("%d\n", ft_atoi("100"));
// 	printf("%d\n", ft_atoi("+100"));
// 	printf("%d, %d\n", ft_atoi("2147483648"), atoi("2147483648"));
// 	printf("%d, %d\n", ft_atoi("4294967295"), atoi("4294967295"));

// 	printf("%d, %d\n", ft_atoi("9223372036854775808"),
// 			atoi("9223372036854775808"));
// 	printf("%d, %d\n",
// 			ft_atoi("-9223372036854775809"),
// 			atoi("-9223372036854775809"));
// 	printf("%d, %d\n",
// 			ft_atoi("18446744073709551616"),
// 			atoi("18446744073709551616"));
// 	printf("%d, %d\n",
// 			ft_atoi("18446744073709551616"),
// 			atoi("18446744073709551616"));
// }