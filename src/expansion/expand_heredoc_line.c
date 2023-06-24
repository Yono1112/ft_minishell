/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:03:26 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/24 22:41:04 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line, t_env **env)
{
	char	*current_word;
	char	*new_word;

	current_word = line;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("ft_calloc");
	while (*current_word)
	{
		if (is_expand_variable(current_word))
		{
			// printf("expand_variable_str\n");
			expand_variable_str(&new_word, &current_word, current_word, env);
		}
		else if (is_special_parametar(current_word))
		{
			// printf("expand_parameter_str\n");
			expand_parameter_str(&new_word, &current_word, current_word);
		}
		else
		{
			// printf("append_char\n");
			append_char(&new_word, *current_word);
			current_word++;
		}
	}
	free(line);
	return (new_word);
}
