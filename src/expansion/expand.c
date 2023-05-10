/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:13:20 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/10 19:39:17 by yumaohno         ###   ########.fr       */
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
		strncpy(new, *s, len);
	new[len - 2] = c;
	new[len - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

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

static void	remove_quote(t_token *token)
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
				remove_single_quote(&new_word, &p, p);
			// {
			// 	p++;
			// 	while (*p != SINGLE_QUOTE_CHAR)
			// 	{
			// 		if (*p == '\0')
			// 			assert_error("Unclosed single quote");
			// 		append_char(&new_word, *p++);
			// 	}
			// 	p++;
			// }
			else if (*p == DOUBLE_QUOTE_CHAR)
				remove_double_quote(&new_word, &p, p);
			// {
			// 	p++;
			// 	while (*p != DOUBLE_QUOTE_CHAR)
			// 	{
			// 		if (*p == '\0')
			// 			assert_error("Unclosed single quote");
			// 		append_char(&new_word, *p++);
			// 	}
			// 	p++;
			// }
			else
				append_char(&new_word, *p++);
		}
		free(token->word);
		token->word = new_word;
		token = token->next;
	}
}

void	expand_quote_removal(t_node *node)
{
	if (node == NULL)
		return ;
	remove_quote(node->args);
	remove_quote(node->filename);
	remove_quote(node->delimiter);
	expand_quote_removal(node->redirects);
	expand_quote_removal(node->next);
}

void	expand(t_node *node)
{
	expand_quote_removal(node);
}
