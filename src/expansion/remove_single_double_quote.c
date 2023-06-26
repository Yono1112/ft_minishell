/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_single_double_quote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:33:36 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:33:45 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_double_quote(char **dst, char **rest, char *p)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				fatal_error("Unclosed double quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		fatal_error("Expected double quote");
}

void	remove_single_quote(char **dst, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		p++;
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				fatal_error("Unclosed single quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		fatal_error("Expected single quote");
}
