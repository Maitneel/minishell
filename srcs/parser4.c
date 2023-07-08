/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:06:45 by dummy             #+#    #+#             */
/*   Updated: 2023/07/08 17:14:20 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_xcalloc.h"
#include <stdlib.h>
#include <string.h>

void	*free_args_list(t_args_list *front)
{
	t_args_list	*next;

	while (front != NULL)
	{
		next = front->next;
		free(front->string);
		free(front);
		front = next;
	}
	return (NULL);
}

t_args_list	*new_args_list(char *string)
{
	t_args_list	*args;

	args = ft_xcalloc(1, sizeof(t_args_list));
	if (args == NULL)
	{
		return (NULL);
	}
	args->string = strdup(string);
	if (args->string == NULL)
	{
		free(args);
		return (NULL);
	}
	return (args);
}

void	push_back_args_list(t_args_list **front, t_args_list *node)
{
	t_args_list	*current;

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
