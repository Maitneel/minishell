/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:40:59 by dummy             #+#    #+#             */
/*   Updated: 2023/05/16 21:56:38 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

typedef struct s_string
{
	char	*data;
	size_t	max_length;
	size_t	length;
}			t_string;

t_string	*init_string(t_string *string, size_t length);
t_string	*push_back_string(t_string *dest, char *src);

#endif