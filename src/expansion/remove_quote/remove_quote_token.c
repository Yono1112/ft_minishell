/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:31:59 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:32:13 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote_token(t_token *token)
{
	char	*p;
	char	*new_word;

	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
	{
		p = token->word;
		new_word = ft_calloc(1, sizeof(char));
		if (new_word == NULL)
			fatal_error("ft_calloc");
		while (*p != '\0')
		{
			if (*p == SINGLE_QUOTE_CHAR)
				remove_single_quote(&new_word, &p, p);
			else if (*p == DOUBLE_QUOTE_CHAR)
				remove_double_quote(&new_word, &p, p);
			else
				append_char(&new_word, *p++);
		}
		free(token->word);
		token->word = new_word;
		token = token->next;
	}
}
