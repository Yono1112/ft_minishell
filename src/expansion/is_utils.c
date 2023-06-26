/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:26:29 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:27:33 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_expand_variable(char *s)
{
	return (s[0] == '$' && is_alpha_under(s[1]));
}

bool	is_special_parametar(char *str)
{
	return (str[0] == '$' && str[1] == '?');
}

bool	is_quote_after_dollar(char *str)
{
	return (str[0] == '$'
		&& (str[1] == SINGLE_QUOTE_CHAR || str[1] == DOUBLE_QUOTE_CHAR));
}

bool	is_metacharacter(char c)
{
	if (is_blank(c))
		return (true);
	return (c && ft_strchr("|&;()<>\n", c));
}
