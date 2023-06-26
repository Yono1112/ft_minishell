/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:53:50 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 00:54:02 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*pipeline(t_token **rest, t_token *token, int *syntax_error)
{
	t_node	*node;

	node = create_new_node_list(ND_PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&token, token, syntax_error);
	if (check_operator(token, "|"))
		node->next = pipeline(&token, token->next, syntax_error);
	*rest = token;
	return (node);
}
