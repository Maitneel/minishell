/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:50:58 by dummy             #+#    #+#             */
/*   Updated: 2023/06/28 00:21:36 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_LIB_H
# define PRINT_LIB_H

void			put_command_not_found(char *command);
void			print_unclosed_quote(void);
void			print_syntax_error(t_token *token);

#endif