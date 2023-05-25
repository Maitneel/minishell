/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:43:36 by taksaito          #+#    #+#             */
/*   Updated: 2023/01/22 14:38:33 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del == NULL)
		return ;
	delone(lst, del);
}

// #include <stdio.h>
// void	print_list(t_list *lst)
// {
// 	if (lst == NULL)
// 		return ;
// 	printf("%s\n", (char *)(lst->content));
// 	print_list(lst->next);
// }

// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list *lst;
// 	char *c = malloc(10);
// 	lst = ft_lstnew((void *)(c));
// 	ft_lstdelone(lst, del);
// 	print_list(lst);
// }