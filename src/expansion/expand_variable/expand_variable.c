/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:57:57 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:32:55 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variable(t_node *node, t_env **env)
{
	while (node != NULL)
	{
		if (node->command != NULL)
			expand_variable_token(node->command->args, env);
		if (node->command->redirects != NULL)
			expand_variable_token(node->command->redirects->filename, env);
		node = node->next;
	}
}
