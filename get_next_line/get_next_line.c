/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:22:41 by dummy             #+#    #+#             */
/*   Updated: 2023/06/18 16:41:36 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static t_buffer	buf[FD_MAX];
	t_string		result;
	char			temp[1];

	result.str = NULL;
	result.max_size = 0;
	result.size = 0;
	if (fd < 0 || FD_MAX <= fd)
		return (NULL);
	buf[fd].loop_flag = read(fd, temp, 0);
	while (buf[fd].loop_flag == 0)
	{
		if (buf[fd].start == 0)
		{
			buf[fd].read_ret = read(fd, buf[fd].str, BUFFER_SIZE);
			if (buf[fd].read_ret <= 0)
				break ;
		}
		add_back_string(&result, &buf[fd]);
	}
	if (buf[fd].loop_flag == -1 || buf[fd].read_ret == -1)
		free(result.str);
	if (buf[fd].loop_flag == -1 || buf[fd].read_ret == -1)
		result.str = NULL;
	return (result.str);
}

void	add_back_string(t_string *data, t_buffer *buf)
{
	char	*new_str;
	size_t	i;

	new_str = malloc(sizeof(char) * (data->size + (buf->read_ret - buf->start)
				+ 1));
	if (new_str == NULL)
		buf->loop_flag = -1;
	else
		data->max_size = data->size + (buf->read_ret - buf->start) + 1;
	i = -1;
	while (++i < data->size && buf->loop_flag == 0)
		new_str[i] = data->str[i];
	free(data->str);
	if (buf->loop_flag != 0)
		return ;
	while (buf->start < buf->read_ret && buf->loop_flag == 0)
	{
		new_str[data->size++] = buf->str[buf->start++];
		if (buf->str[buf->start - 1] == '\n')
			buf->loop_flag = 1;
	}
	new_str[data->size] = '\0';
	if (buf->start == buf->read_ret)
		buf->start = 0;
	data->str = new_str;
}
