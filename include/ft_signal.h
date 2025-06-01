/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:12:38 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 18:18:59 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <unistd.h>

typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}						t_pid_list;

void					resive_signal(int sig_id);
t_pid_list				*pid_push_back(t_pid_list **list, pid_t pid);
void					*free_pid_list(t_pid_list **pid_list);

#endif