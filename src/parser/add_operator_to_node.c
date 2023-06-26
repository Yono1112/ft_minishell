/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_operator_to_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:01:40 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 01:01:52 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
