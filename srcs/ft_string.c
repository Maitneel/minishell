/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:41:45 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:28:06 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_xcalloc.h"
#include "libft.h"
#include <stdlib.h>


t_string	*init_string(t_string *string, size_t length)
{
	if (string == NULL || length == 0 || length == SIZE_MAX)
		return (NULL);
	string->data = ft_xcalloc(sizeof(char), length + 1);
	if (string->data == NULL)
		return (NULL);
	string->length = 0;
	string->max_length = length;
	return (string);
}

static t_string	*resize_string(t_string *string, size_t resize_length)
{
	char	*resized_string;
	size_t	i;

	if (string == NULL)
		return (NULL);
	if (resize_length < string->length || resize_length == SIZE_MAX)
	{
		free(string->data);
		return (NULL);
	}
	resized_string = ft_xcalloc(sizeof(char), resize_length + 1);
	if (resized_string == NULL)
	{
		free(string->data);
		return (NULL);
	}
	i = -1;
	while (++i < string->length && string->data != NULL)
		resized_string[i] = string->data[i];
	free(string->data);
	string->data = resized_string;
	string->max_length = resize_length;
	return (string);
}

static size_t	get_resize_length(t_string *string, size_t src_length)
{
	size_t	resize_len;

	if (string == NULL)
		return (0);
	resize_len = string->max_length;
	if (string->length == SIZE_MAX || src_length == SIZE_MAX)
		return (0);
	if (SIZE_MAX - src_length < string->length + 1)
		return (0);
	while (resize_len < src_length + string->length && resize_len < SIZE_MAX
		/ 2)
	{
		resize_len *= 2;
	}
	if (resize_len < src_length + string->length)
		resize_len = SIZE_MAX;
	return (resize_len);
}

t_string	*push_back_string(t_string *dest, char *src)
{
	size_t	src_length;
	size_t	i;

	if (dest == NULL || src == NULL)
		return (dest);
	src_length = ft_strlen(src);
	if (SIZE_MAX - src_length < dest->length)
	{
		free(dest->data);
		return (NULL);
	}
	if (dest->max_length < dest->length + src_length)
	{
		if (resize_string(dest, get_resize_length(dest, src_length)) == NULL)
			return (NULL);
	}
	i = 0;
	while (i < src_length)
	{
		dest->data[i + dest->length] = src[i];
		i++;
	}
	dest->length += src_length;
	return (dest);
}

t_string	*set_string(t_string *struct_string, char *string_ptr)
{
	if (struct_string == NULL)
		return (NULL);
	struct_string->data = string_ptr;
	struct_string->length = 0;
	struct_string->max_length = 0;
	if (string_ptr == NULL)
		return (NULL);
	struct_string->length = ft_strlen(string_ptr);
	struct_string->max_length = struct_string->length;
	return (struct_string);
}

// 
// int main() {
// 	t_string string;

// 	size_t before_push_back_maxlength;
// 	if (init_string(&string, 4) == NULL)
// 	{
// 		printf("init error\n");
// 		return (1);
// 	}
// 	before_push_back_maxlength = string.max_length;
// 	push_back_string(&string, "aaa");
// 	if (before_push_back_maxlength != string.max_length) {
// 		printf("resize\n");
// 	}
// 	printf("len : %5zu, max_len : %5zu, str : %s\n", string.length,
//			string.max_length, string.data);
// 	for (size_t i = 0; i < 100; i++)
// 	{
// 		before_push_back_maxlength = string.max_length;
// 		push_back_string(&string, "hogefuga");
// 		if (before_push_back_maxlength != string.max_length) {
// 			printf("resize\n");
// 		}
// 		printf("len : %5zu, max_len : %5zu, str : %s\n", string.length,
//				string.max_length, string.data);
// 	}
// 	return (0);
// }