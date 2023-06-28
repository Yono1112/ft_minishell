/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:33:23 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 00:46:16 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_node *node, t_env **env)
{
	int		status;

	status = 0;
	if (open_redirect_file(node, env) < 0 || g_data.readline_interrupted)
		status = 1;
	else if (node->next == NULL && is_builtin(node))
		status = exec_builtin_cmd(node, env);
	else
		status = exec_cmd(node, env);
	return (status);
}
