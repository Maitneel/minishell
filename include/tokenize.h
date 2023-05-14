/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:49:12 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/14 16:13:09 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

typedef struct s_token
{
	char			*word;
	int				kind;
	struct s_token	*next;
}	t_token;

typedef struct s_tokenize
{
	t_token *tokens;
}	t_tokenize;

t_tokenize	*tokenize(char *line);

#endif
