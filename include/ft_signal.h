/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:12:38 by dummy             #+#    #+#             */
/*   Updated: 2023/06/01 15:11:44 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

typedef enum e_runnning_status
{
    UNDEFINED = 2000,
    READING_PROMPT,
}   t_running_status;

typedef struct s_signal_struct
{
    t_running_status status;
}				t_sginal_struct;

void			resive_signal(int sig_id);

t_sginal_struct	signal_info;

#endif