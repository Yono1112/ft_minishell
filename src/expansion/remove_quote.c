/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:46:09 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/03 20:44:46 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_double_quote(char **dst, char **rest, char *p)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed double quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected double quote");
}

void	remove_single_quote(char **dst, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		p++;
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				assert_error("Unclosed single quote");
			append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		assert_error("Expected single quote");
}

static void	remove_quote_token(t_token *token)
{
	char	*p;
	char	*new_word;

	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
	{
		// printf("token->word: %s\n", token->word);
		p = token->word;
		new_word = NULL;
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
		// printf("remove_quote token->word: %s\n", token->word);
		token = token->next;
	}
}

void	remove_quote(t_node *node)
{
	while (node != NULL)
	{
		if (node->command != NULL)
			remove_quote_token(node->command->args);
		if (node->command->redirects != NULL)
		{
			remove_quote_token(node->command->redirects->filename);
			remove_quote_token(node->command->redirects->delimiter);
		}
		node = node->next;
	}
}

// void	expand_quote_removal(t_node *node)
// {
// 	if (node == NULL)
// 		return ;
// 	remove_quote(node->args);
// 	remove_quote(node->filename);
// 	remove_quote(node->delimiter);
// 	expand_quote_removal(node->redirects);
// 	expand_quote_removal(node->command);
// 	expand_quote_removal(node->next);
// }
