/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:17:59 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 21:14:14 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_word(char *line)
{
	return (!is_blank(*line) && !is_operator(line));
}

static void	check_error(char quote, char **line, int *syntax_error)
{
	(*line)++;
	while (**line != quote)
	{
		if (**line == '\0')
		{
			if (quote == '\'')
				tokenize_error(ERROR_SINGLE, line, *line, syntax_error);
			else
				tokenize_error(ERROR_DOUBLE, line, *line, syntax_error);
			break ;
		}
		(*line)++;
	}
	(*line)++;
}

t_token	*add_word_to_list(char **rest_line, char *line, int *syntax_error)
{
	char	*word;
	char	*start;

	start = line;
	word = NULL;
	while (*line && is_word(line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
			check_error(SINGLE_QUOTE_CHAR, &line, syntax_error);
		else if (*line == DOUBLE_QUOTE_CHAR)
			check_error(DOUBLE_QUOTE_CHAR, &line, syntax_error);
		else
			line++;
	}
	word = ft_strndup(start, line - start);
	if (word == NULL)
		fatal_error("ft_strndup");
	*rest_line = line;
	return (create_new_token_list(word, TK_WORD));
}
