/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:21:10 by dummy             #+#    #+#             */
/*   Updated: 2023/06/18 18:08:12 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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

typedef struct s_gnl_string
{
	char	*str;
	size_t	size;
	size_t	max_size;
}			t_gnl_string;

char		*get_next_line(int fd);
void		add_back_string(t_gnl_string *data, t_buffer *buf);

#endif
