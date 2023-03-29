/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:17:59 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/29 16:18:22 by yumaohno         ###   ########.fr       */
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
	while (*line && is_word(line))
		line++;
	word = strndup(start, line - start);
	printf("word: %s\n", word);
	if (word == NULL)
		fatal_error("strndup");
	*rest_line = line;
	return (create_new_token_list(word, TK_WORD));
}