/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:13:20 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/29 22:11:07 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_char(char **s, char c)
{
	size_t	len;
	char	*new;

	if (*s)
		len = strlen(*s) + 2;
	else
		len = 2;
	new = malloc(len);
	if (!new)
		fatal_error("malloc");
	if (*s)
		strlcpy(new, *s, len);
	new[len - 2] = c;
	new[len - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

static void	quote_removal(t_token *token)
{
	char	*p;
	char	*new_word;

	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
	{
		p = token->word;
		new_word = NULL;
		while (*p != '\0')
		{
			if (*p == SINGLE_QUOTE_CHAR)
			{
				p++;
				while (*p != SINGLE_QUOTE_CHAR)
				{
					if (*p == '\0')
						todo("Unclosed single quote");
					append_char(&new_word, *p++);
				}
				p++;
			}
			else if (*p == DOUBLE_QUOTE_CHAR)
			{
				p++;
				while (*p != DOUBLE_QUOTE_CHAR)
				{
					if (*p == '\0')
						todo("Unclosed double quote");
					append_char(&new_word, *p++);
				}
				p++;
			}
			else
				append_char(&new_word, *p++);
		}
		free(token->word);
		token->word = new_word;
		token = token->next;
	}
}

void	expand(t_token *token)
{
	quote_removal(token);
}
