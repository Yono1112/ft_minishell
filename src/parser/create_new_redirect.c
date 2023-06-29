/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:58:07 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 11:11:16 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_new_redirect_out(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_OUT);
	node->filename = tokendup(token->next);
	node->std_fd = STDOUT_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*create_new_redirect_in(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_IN);
	node->filename = tokendup(token->next);
	node->std_fd = STDIN_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*create_new_redirect_append(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_APPEND);
	node->filename = tokendup(token->next);
	node->std_fd = STDOUT_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*create_new_redirect_heredoc(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_HEREDOC);
	node->delimiter = tokendup(token->next);
	node->std_fd = STDIN_FILENO;
	if (ft_strchr(node->delimiter->word, SINGLE_QUOTE_CHAR) == NULL
		&& ft_strchr(node->delimiter->word, DOUBLE_QUOTE_CHAR) == NULL)
		node->is_delimiter_quote = true;
	*rest = token->next->next;
	return (node);
}
