/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:46:09 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 03:34:59 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(t_node *node)
{
	while (node != NULL)
	{
		if (node->command != NULL)
			remove_quote_token(node->command->args);
		if (node->command->redirects != NULL)
		{
			remove_quote_token(node->command->redirects->filename);
			remove_quote_token(node->command->redirects->delimiter);
		}
		node = node->next;
	}
}
