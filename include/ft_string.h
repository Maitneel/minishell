/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:40:59 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:27:59 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

# define DEFAULT_INIT_SIZE 1024

typedef struct s_string
{
	char	*data;
	size_t	max_length;
	size_t	length;
}			t_string;

t_string	*init_string(t_string *string, size_t length);
t_string	*push_back_string(t_string *dest, char *src);
t_string	*push_back_string_char(t_string *string, char c);
t_string	*set_string(t_string *struct_string, char *string_ptr);
int			ft_strcmp(const char *s1, const char *s2);

#endif