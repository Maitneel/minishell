/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:19:25 by dummy             #+#    #+#             */
/*   Updated: 2023/07/21 16:45:21 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_ENV_H
# define EXPAND_ENV_H

char		*get_expande_pipe(char *env_ptr, bool is_expand, char quote_flag);
t_string	*expand_env(t_string *expanded, t_string *line,
				t_env_manager *env_manager);

#endif