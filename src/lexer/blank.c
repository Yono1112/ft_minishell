/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:03:53 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/29 17:04:20 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	skip_blank(char **skip_line, char *line)
{
	while (is_blank(*line))
		line++;
	*skip_line = line;
}
