/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_no_exist_file_name.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:13:47 by dummy             #+#    #+#             */
/*   Updated: 2023/06/22 20:18:39 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

size_t	ft_pow(size_t x, size_t y)
{
	size_t	result;

	result = 1;
	while (y)
	{
		result *= x;
		y--;
	}
	return (result);
}

char	*setup_file_name(char *front_string, size_t front_len, size_t num_len)
{
	size_t	i;
	char	*file_name;

	file_name = ft_calloc(sizeof(char), front_len + 1 + num_len + 1);
	if (file_name == NULL)
		return (NULL);
	ft_memcpy(file_name, front_string, front_len);
	file_name[front_len] = '-';
	i = -1;
	while (++i < num_len)
	{
		file_name[front_len + 1 + i] = '0';
	}
	return (file_name);
}

char	*generate_no_exist_file_name(char *front_string)
{
	char	*file_name;
	int		num;
	size_t	i;
	size_t	front_len;
	bool	carry;

	front_len = ft_strlen(front_string);
	file_name = setup_file_name(front_string, front_len, 8);
	if (file_name == NULL)
		return (NULL);
	num = -1;
	while (++num < 100000000)
	{
		i = 8;
		while (i == 8 || (i && carry))
		{
			file_name[front_len + i] = '0' + ((num / ft_pow(10, 8 - i)) % 10);
			carry = (file_name[front_len + i] == '0');
			i--;
		}
		if (access(file_name, F_OK) == -1)
			return (file_name);
	}
	file_name[front_len] = '\0';
	return (NULL);
}

// int	main(void)
// {
// 	printf("ret : %s\n", generate_no_exist_file_name("/tmp/hogehoge"));
// }
