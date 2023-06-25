/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:16:31 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/29 03:35:15by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_new_token_list(char *word, t_token_kind kind)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		fatal_error("malloc");
	new_token->word = word;
	new_token->kind = kind;
	new_token->next = NULL;
	return (new_token);
}

t_token	*tokenize(char	*line, int *syntax_error)
{
	t_token	head;
	t_token	*token;

	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (is_blank(*line))
			skip_blank(&line, line);
		else if (is_operator(line))
		{
			token->next = add_operator_to_list(&line, line);
			token = token->next;
		}
		else if (is_word(line))
		{
			token->next = add_word_to_list(&line, line, syntax_error);
			token = token->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line, syntax_error);
			// assert_error("Unexpected Token");
		// token = token->next;
	}
	token->next = create_new_token_list(NULL, TK_EOF);
	return (head.next);
}
