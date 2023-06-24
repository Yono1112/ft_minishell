/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:17:59 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/25 00:54:20 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_word(char *line)
{
	return (!is_blank(*line) && !is_operator(line));
}

t_token	*add_word_to_list(char **rest_line, char *line)
{
	char	*word;
	char	*start;

	start = line;
	word = NULL;
	while (*line && is_word(line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
		{
			line++;
			while (*line != SINGLE_QUOTE_CHAR)
			{
				if (*line == '\0')
				{
					tokenize_error("Unclosed single quote", &line, line);
					break ;
				}
				line++;
			}
			line++;
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			line++;
			while (*line != DOUBLE_QUOTE_CHAR)
			{
				if (*line == '\0')
				{
					tokenize_error("Unclosed double quote", &line, line);
					break ;
				}
				line++;
			}
			line++;
		}
		else
			line++;
	}
	word = ft_strndup(start, line - start);
	// printf("word: %s\n", word);
	if (word == NULL)
		fatal_error("ft_strndup");
	*rest_line = line;
	return (create_new_token_list(word, TK_WORD));
}
