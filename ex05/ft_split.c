// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_split.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/04 13:24:20 by dummy             #+#    #+#             */
// /*   Updated: 2023/05/10 01:30:29 by dummy            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "ms_lib.h"
// #include <stdbool.h>
// #include <stddef.h>
// #include <stdlib.h>

// static bool	is_charset(char *charset, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (charset[i])
// 	{
// 		if (charset[i] == c)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// static size_t	get_split_size(char const *s, char *charset)
// {
// 	size_t	result;
// 	size_t	i;

// 	result = 0;
// 	if (s[0] == '\0')
// 	{
// 		return (0);
// 	}
// 	i = 1;
// 	while (s[i] != '\0')
// 	{
// 		if (is_charset(charset, s[i]) && !is_charset(charset, s[i - 1]))
// 		{
// 			result++;
// 		}
// 		i++;
// 	}
// 	if (i != 0)
// 	{
// 		if (!is_charset(charset, s[i - 1]))
// 		{
// 			result++;
// 		}
// 	}
// 	return (result);
// }

// static void	*all_free(char **s, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < size && size != 0)
// 	{
// 		free(s[i]);
// 		i++;
// 	}
// 	free(s);
// 	return (NULL);
// }

// static char	*get_next_string(const char *s, char *charset, size_t *plus)
// {
// 	size_t	len;
// 	char	*result;

// 	*plus = 0;
// 	while (is_charset(charset, *s) && *s != '\0')
// 	{
// 		(*plus)++;
// 		s++;
// 	}
// 	len = 0;
// 	while (!is_charset(charset, s[len]) && s[len] != '\0')
// 	{
// 		(*plus)++;
// 		len++;
// 	}
// 	if (len == 0)
// 	{
// 		return (NULL);
// 	}
// 	result = (ft_substr(s, 0, len));
// 	return (result);
// }

// char	**ft_split_use_charset(char const *s, char *charset)
// {
// 	size_t	split_size;
// 	size_t	split_index;
// 	size_t	plus;
// 	char	**split;

// 	if (s == NULL)
// 		return (NULL);
// 	split_size = get_split_size(s, charset) + 1;
// 	split = malloc(sizeof(char *) * split_size);
// 	if (split == NULL)
// 		return (NULL);
// 	plus = 0;
// 	while (plus < split_size && (++plus || 1))
// 		split[plus - 1] = NULL;
// 	split_index = 0;
// 	while (split_index < split_size - 1)
// 	{
// 		split[split_index] = get_next_string(s, charset, &plus);
// 		s += plus;
// 		if (split[split_index] == NULL)
// 			return (all_free(split, split_index));
// 		split_index++;
// 	}
// 	split[split_size - 1] = NULL;
// 	return (split);
// }
