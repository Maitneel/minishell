/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:12:38 by dummy             #+#    #+#             */
/*   Updated: 2023/06/08 15:26:18 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

#include <unistd.h>
typedef enum e_runnning_status
{
    UNDEFINED = 2000,
    READING_PROMPT,
    EXECUTING_COMMAND,
}   t_running_status;

typedef struct s_pid_list
{
    pid_t pid;
    struct s_pid_list *next;
} t_pid_list;


typedef struct s_signal_struct
{
    t_running_status status;
    t_pid_list *pid_list;
}				t_sginal_struct;

void			resive_signal(int sig_id);
t_pid_list		*pid_push_back(t_pid_list **list, pid_t pid);
void            *free_pid_list(t_pid_list **pid_list);

t_sginal_struct	signal_info;

#endif