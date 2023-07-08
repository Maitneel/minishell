/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:04:06 by dummy             #+#    #+#             */
/*   Updated: 2023/07/08 17:13:04 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_xcalloc.h"
#include <stdlib.h>

void	*free_redirect_info(t_redirect_info *front)
{
	t_redirect_info	*next;

	while (front != NULL)
	{
		next = front->next;
		free(front->arg);
		free(front);
		front = next;
	}
	return (NULL);
}

t_redirect_info	*new_redirect_info(void)
{
	t_redirect_info	*redirect_info;

	redirect_info = ft_xcalloc(1, sizeof(t_redirect_info));
	if (redirect_info == NULL)
	{
		return (NULL);
	}
	return (redirect_info);
}

void	push_back_redirect_info(t_redirect_info **front, t_redirect_info *node)
{
	t_redirect_info	*current;

	if (front == NULL)
	{
		return ;
	}
	if (*front == NULL)
	{
		*front = node;
		return ;
	}
	current = *front;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = node;
}
