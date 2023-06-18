/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:21:10 by dummy             #+#    #+#             */
/*   Updated: 2023/06/18 16:23:17 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define FD_MAX 256

typedef struct s_buffer
{
	char	str[BUFFER_SIZE + 1];
	ssize_t	start;
	ssize_t	read_ret;
	ssize_t	loop_flag;
}			t_buffer;

typedef struct s_string
{
	char	*str;
	size_t	size;
	size_t	max_size;
}			t_string;

char		*get_next_line(int fd);
void		add_back_string(t_string *data, t_buffer *buf);

#endif
