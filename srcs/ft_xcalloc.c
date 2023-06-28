/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 22:24:16 by dummy             #+#    #+#             */
/*   Updated: 2023/06/28 22:36:36 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*new_ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	new_ptr = calloc(count, size);
	if (new_ptr == NULL)
	{
		write(STDERR_FILENO, "minishell: failed to allocate memory\n", 38);
		exit(1);
	}
	return (new_ptr);
}
