/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:46:09 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/24 08:56:12 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_double_quote(char **new_word, char **rest, char *current_word)
{
	if (*current_word == DOUBLE_QUOTE_CHAR)
	{
		current_word++;
		while (*current_word != DOUBLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				assert_error("Unclosed double quote");
			append_char(new_word, *current_word++);
		}
		current_word++;
		*rest = current_word;
	}
	else
		assert_error("Expected double quote");
}

void	remove_single_quote(char **new_word, char **rest, char *current_word)
{
	if (*current_word == SINGLE_QUOTE_CHAR)
	{
		current_word++;
		while (*current_word != SINGLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				assert_error("Unclosed single quote");
			append_char(new_word, *current_word++);
		}
		current_word++;
		*rest = current_word;
	}
	else
		assert_error("Expected single quote");
}

// void	remove_single_double_quote(char **new_word, char **rest, char *current_word)
// {
// 	if (*current_word == SINGLE_QUOTE_CHAR)
// 	{
// 		current_word++;
// 		while (*current_word != SINGLE_QUOTE_CHAR)
// 		{
// 			if (*current_word == '\0')
// 				assert_error("Unclosed single quote");
// 			append_char(new_word, *current_word++);
// 		}
// 		current_word++;
// 		*rest = current_word;
// 	}
// 	else if (*current_word == DOUBLE_QUOTE_CHAR)
// 	{
// 		current_word++;
// 		while (*current_word != DOUBLE_QUOTE_CHAR)
// 		{
// 			if (*current_word == '\0')
// 				assert_error("Unclosed double quote");
// 			append_char(new_word, *current_word++);
// 		}
// 		current_word++;
// 		*rest = current_word;
// 	}
// 	else
// 		assert_error("Expected quote");
// }

static void	remove_quote_token(t_token *token, t_env **env)
{
	char	*current_word;
	char	*new_word;

	// printf("start remove_quote_token\n");
	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
	{
		// printf("token->word: %s\n", token->word);
		current_word = token->word;
		new_word = NULL;
		while (*current_word != '\0')
		{
			if (*current_word == SINGLE_QUOTE_CHAR && !is_custom_ifs(SINGLE_QUOTE_CHAR, env))
				remove_single_quote(&new_word, &current_word, current_word);
			else if (*current_word == DOUBLE_QUOTE_CHAR && !is_custom_ifs(DOUBLE_QUOTE_CHAR, env))
				remove_double_quote(&new_word, &current_word, current_word);
			// if (*current_word == SINGLE_QUOTE_CHAR || *current_word == DOUBLE_QUOTE_CHAR)
			// 	remove_single_double_quote(&new_word, &current_word, current_word);
			else
				append_char(&new_word, *current_word++);
		}
		free(token->word);
		token->word = new_word;
		// printf("after token->word: %s\n", token->word);
		token = token->next;
	}
}

void	remove_quote(t_node *node, t_env **env)
{
	while (node != NULL)
	{
		if (node->command != NULL)
			remove_quote_token(node->command->args, env);
		if (node->command->redirects != NULL)
		{
			remove_quote_token(node->command->redirects->filename, env);
			remove_quote_token(node->command->redirects->delimiter, env);
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
