/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:42:06 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/22 14:38:37 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// void	print_list(t_list *lst)
// {
// 	if (lst == NULL)
// 		return ;
// 	printf("%s\n", (char *)(lst->content));
// 	print_list(lst->next);
// }
// int	main(void)
// {
// 	t_list *lst;
// 	t_list *new;
// 	lst = ft_lstnew((void *)("aizu"));
// 	new = malloc(sizeof(t_list));
// 	ft_lstadd_front(&lst, new);
// 	print_list(lst);

// }