/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:19:42 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:19:59 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_single_quote(char **new_word, char **rest, char *current_word)
{
	if (*current_word == SINGLE_QUOTE_CHAR)
	{
		append_char(new_word, *current_word);
		current_word++;
		while (*current_word != SINGLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				fatal_error("Unclosed single quote");
			append_char(new_word, *current_word++);
		}
		append_char(new_word, *current_word);
		current_word++;
		*rest = current_word;
	}
	else
		fatal_error("Expected single quote");
}

void	append_double_quote(char **new_word, char **rest,
			char *current_word, t_env **env)
{
	if (*current_word == DOUBLE_QUOTE_CHAR)
	{
		append_char(new_word, *current_word);
		current_word++;
		while (*current_word != DOUBLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				fatal_error("Unclosed double quote");
			else if (is_expand_variable(current_word))
				expand_variable_str(new_word, &current_word, current_word, env);
			else if (is_special_parametar(current_word))
				expand_parameter_str(new_word, &current_word, current_word);
			else
				append_char(new_word, *current_word++);
		}
		append_char(new_word, *current_word);
		current_word++;
		*rest = current_word;
	}
	else
		fatal_error("Expected double quote");
}
