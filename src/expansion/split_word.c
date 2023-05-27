/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:11:59 by yuohno            #+#    #+#             */
/*   Updated: 2023/05/28 01:56:46 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	split_word_token(t_token *token)
// {
// 	char	*current_word;
// 	char	*new_word;
// 
// 	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
// 	{
// 		current_word = token->word;
// 		new_word = NULL;
// 		while (*current_word != '\0')
// 		{
// 			if (*current_word == SINGLE_QUOTE_CHAR || *current_word == DOUBLE_QUOTE_CHAR)
// 				remove_single_double_quote(&new_word, &current_word, current_word);
// 			else
// 				append_char(&new_word, *current_word++);
// 		}
// 		free(token->word);
// 		token->word = new_word;
// 		token = token->next;
// 	}
// }
// 
// void	split_word(t_node *node)
// {
// 	while (node != NULL)
// 	{
// 		if (node->command != NULL)
// 			split_word_token(node->command->args);
// 		if (node->command->redirects != NULL)
// 		{
// 			split_word_token(node->command->redirects->filename);
// 			split_word_token(node->command->redirects->delimiter);
// 		}
// 		node = node->next;
// 	}
// }
