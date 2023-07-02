/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:05:49 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/02 18:13:58 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_xsplit.h"
#include "ft_xcalloc.h"

char	**ft_xsplit(const char *str, char sep)
{
	char	**splited;

	splited = ft_split(str, sep);
	if (splited == NULL)
		ft_exit(ALOCATE_ERROR);
	return (splited);
}
