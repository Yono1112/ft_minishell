/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:31:59 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 14:59:56 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote_token(t_token *token)
{
	char	*current_word;
	char	*new_word;

	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
	{
		current_word = token->word;
		new_word = ft_calloc(1, sizeof(char));
		if (new_word == NULL)
			fatal_error("ft_calloc");
		while (*current_word != '\0')
		{
			if (*current_word == SINGLE_QUOTE_CHAR)
				remove_single_quote(&new_word, &current_word, current_word);
			else if (*current_word == DOUBLE_QUOTE_CHAR)
				remove_double_quote(&new_word, &current_word, current_word);
			else
				append_char(&new_word, *current_word++);
		}
		free(token->word);
		token->word = new_word;
		token = token->next;
	}
}
