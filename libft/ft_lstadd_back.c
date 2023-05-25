/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:43:17 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/22 14:38:35 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		rec(&(*lst)->next, new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	rec(lst, new);
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
// 	t_list *lst = NULL;
// 	t_list *elem1 = calloc(sizeof(t_list), 1);
// 	t_list *elem2 = calloc(sizeof(t_list), 1);
// 	t_list *elem3 = calloc(sizeof(t_list), 1);
// 	t_list *elem4 = calloc(sizeof(t_list), 1);
// 	t_list *elem5 = calloc(sizeof(t_list), 1);
// 	char *s1 = "hello";
// 	char *s2 = "world";
// 	char *s3 = "42!";
// 	int val4 = 42;
// 	int val5 = -42;
// 	elem1->content = s1;
// 	elem2->content = s2;
// 	elem3->content = s3;
// 	elem4->content = &val4;
// 	elem5->content = &val5;

// 	/* Add back #1 */
// 	ft_lstadd_back(&lst, elem1);
// 	print_list(lst);
// }