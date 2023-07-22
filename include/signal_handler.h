/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:03:12 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 17:34:19 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

void	heredoc_signal_handler(int sig_id);
void	readline_signal_handler(int sig_id);
void	signal_handler(int sig_id);
void	heredoc_child_signal_handler(int sig_id);
void	register_signal_handler(void (*handler)(int));

#endif