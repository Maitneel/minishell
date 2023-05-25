/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:14:29 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/14 01:57:18 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	new_n;

	if (n == 0)
		ft_putchar_fd(n + 48, fd);
	else if (n > 0)
	{
		new_n = n / 10;
		if (new_n != 0)
			ft_putnbr_fd(new_n, fd);
		ft_putchar_fd(n % 10 + 48, fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		new_n = 0 - (n / 10);
		if (new_n != 0)
			ft_putnbr_fd(new_n, fd);
		ft_putchar_fd(0 - (n % 10) + 48, fd);
	}
}
