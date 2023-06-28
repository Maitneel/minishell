/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 22:31:22 by dummy             #+#    #+#             */
/*   Updated: 2023/06/29 03:48:45 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_XCALLOC_H
# define FT_XCALLOC_H

# include <stddef.h>

typedef enum s_error_enum
{
	UNKNOWN = 5000,
	ALOCATE_ERROR,
}		t_error_enum;

void	*ft_xcalloc(size_t count, size_t size);
void	ft_exit(t_error_enum error_type);

#endif