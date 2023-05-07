/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:17:59 by yumaohno          #+#    #+#             */
/*   Updated: 2023/04/10 16:00:62by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_to_node(t_token **node_token, t_token *new_token)
{
	t_token	*tmp_token;

	if (*node_token == NULL)
		*node_token = new_token;
	else
	{
		tmp_token = *node_token;
		while (tmp_token->next != NULL)
			tmp_token = tmp_token->next;
		tmp_token->next = new_token;
	}
}

void	add_operator_to_node(t_node **node, t_node *new_node)
{
	t_node	*tmp_node;

	if (*node == NULL)
		*node = new_node;
	else
	{
		tmp_node = *node;
		while (tmp_node->next != NULL)
			tmp_node = tmp_node->next;
		tmp_node->next = new_node;
	}
}

t_token	*tokendup(t_token *token)
{
	char	*word;

	word = strdup(token->word);
	if (word == NULL)
		fatal_error("strdup");
	return (create_new_token_list(word, token->kind));
}

t_node	*create_new_node_list(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

bool	check_operator(t_token *token, char *op)
{
	return (token->kind == TK_OP || strcmp(token->word, op) == 0);
}

t_node	*create_new_redirect(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_OUT);
	node->filename = tokendup(token->next);
	node->targetfd = STDOUT_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*parse(t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_SIMPLE_CMD);
	while (token && token->kind != TK_EOF)
	{
		// printf("token_kind: %u\n", token->kind);
		if (token->kind == TK_WORD)
		{
			add_token_to_node(&node->args, tokendup(token));
			token = token->next;
		}
		else if (check_operator(token, ">") && token->next->kind == TK_WORD)
			add_operator_to_node(&node->redirects, create_new_redirect(&token, token));
		else
			todo("Implement parser");
	}
	return (node);
}
