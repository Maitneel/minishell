/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:43:59 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/22 14:38:39 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (*lst == NULL)
		return ;
	next = (*lst)->next;
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
	rec(&next, del);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	rec(lst, del);
}
