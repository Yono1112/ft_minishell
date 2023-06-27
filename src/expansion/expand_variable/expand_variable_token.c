/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:35:13 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:29:48 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_variable_token_while(t_env **env,
			char **new_word, char **current_word)
{
	while (**current_word && !is_metacharacter(**current_word))
	{
		if (**current_word == SINGLE_QUOTE_CHAR)
			append_single_quote(new_word, current_word, *current_word);
		else if (**current_word == DOUBLE_QUOTE_CHAR)
			append_double_quote(new_word, current_word, *current_word, env);
		else if (is_expand_variable(*current_word))
			expand_variable_str(new_word, current_word, *current_word, env);
		else if (is_special_parametar(*current_word))
			expand_parameter_str(new_word, current_word, *current_word);
		else if (is_quote_after_dollar(*current_word))
			(*current_word)++;
		else
			append_char(new_word, *(*current_word)++);
	}
}

void	expand_variable_token(t_token *token, t_env **env)
{
	char	*new_word;
	char	*current_word;

	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
	{
		current_word = token->word;
		new_word = ft_calloc(1, sizeof(char));
		if (new_word == NULL)
			fatal_error("ft_calloc");
		expand_variable_token_while(env, &new_word, &current_word);
		free(token->word);
		token->word = new_word;
		token = token->next;
	}
}
