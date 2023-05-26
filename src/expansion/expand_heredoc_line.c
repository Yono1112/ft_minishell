/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:03:26 by yuohno            #+#    #+#             */
/*   Updated: 2023/05/24 20:30:04 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line)
{
	char	*current_word;
	char	*new_word;

	current_word = line;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*current_word)
	{
		if (is_variable(current_word))	
			expand_variable_str(&new_word, &current_word, current_word);
		else if (is_special_parametar(current_word))
			expand_parameter_str(&new_word, &current_word, current_word);
		else
		{
			append_char(&new_word, *current_word);
			current_word++;
		}
	}
	free(line);
	return (new_word);
}
