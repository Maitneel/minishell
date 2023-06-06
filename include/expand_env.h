/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:19:25 by dummy             #+#    #+#             */
/*   Updated: 2023/06/06 18:29:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_ENV_H
# define EXPAND_ENV_H

t_string *expand_env(t_string *expanded, t_string *line, t_env_manager *env_manager);

#endif