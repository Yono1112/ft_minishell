/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:11:59 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/23 23:53:48 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_token_with_ifs(char **new_word, char **rest, char *curretn_word, t_token *token)
{

}

void	split_word_token(t_token *token)
{
	char	*current_word;
	char	*new_word;
	char	*free_word;

	current_word = (token->word);
	free_word = token->word;
	new_word = calloc(1, size_t(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*current_word != '\0')
	{
		if (*current_word == SINGLE_QUOTE_CHAR)
			remove_single_double_quote(&new_word, &current_word, current_word);
		else if (*current_word == DOUBLE_QUOTE_CHAR)
			remove_single_double_quote(&new_word, &current_word, current_word);
		else if (is_ifs_word(*current_word))
			split_token_with_ifs(&new_word, &current_word, current_word, token);
		else
			append_char(&new_word, *current_word++);
	}
	token->word = new_word;
	free(free_word);
}

void	split_word(t_node *node)
{
	while (node != NULL)
	{
		if (node->command != NULL)
			split_word_token(node->command->args);
		if (node->command->redirects != NULL)
			split_word_token(node->command->redirects->filename);
		node = node->next;
	}
}
