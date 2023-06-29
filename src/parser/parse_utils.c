/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:03:08 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 01:06:14 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokendup(t_token *token)
{
	char	*word;

	word = ft_strdup(token->word);
	if (word == NULL)
		fatal_error("ft_strdup");
	return (create_new_token_list(word, token->kind));
}

t_node	*create_new_node_list(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("ft_calloc");
	node->kind = kind;
	return (node);
}

bool	check_operator(t_token *token, char *op)
{
	return (token->kind == TK_OP && ft_strcmp(token->word, op) == 0);
}
