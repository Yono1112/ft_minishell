/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_single_double_quote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:33:36 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 14:55:29 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_double_quote(char **dst, char **rest, char *current_word)
{
	if (*current_word == DOUBLE_QUOTE_CHAR)
	{
		current_word++;
		while (*current_word != DOUBLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				fatal_error("Unclosed double quote");
			append_char(dst, *current_word++);
		}
		current_word++;
		*rest = current_word;
	}
	else
		fatal_error("Expected double quote");
}

void	remove_single_quote(char **dst, char **rest, char *current_word)
{
	if (*current_word == SINGLE_QUOTE_CHAR)
	{
		current_word++;
		while (*current_word != SINGLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				fatal_error("Unclosed single quote");
			append_char(dst, *current_word++);
		}
		current_word++;
		*rest = current_word;
	}
	else
		fatal_error("Expected single quote");
}
