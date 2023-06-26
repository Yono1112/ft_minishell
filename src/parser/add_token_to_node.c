/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:00:44 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 01:00:53 by yuohno           ###   ########.fr       */
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
