/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:33:23 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/29 11:50:26 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_node *node, t_env **env)
{
	pid_t	pid;
	int		status;

	if (open_redirect_file(node, env) < 0 || g_data.heredoc_sig_received)
		status = 1;
	else if (node->next == NULL && is_builtin(node))
		status = exec_builtin_cmd(node, env);
	else
	{
		while (node != NULL)
		{
			prepare_pipe(node);
			pid = fork();
			if (pid < 0)
				fatal_error("fork");
			if (pid == CHILD_PID && is_builtin(node))
				exit(exec_builtin_cmd(node, env));
			else if (pid == CHILD_PID)
				exec_simple_cmd(node, env);
			prepare_pipe_parent(node);
			node = node->next;
		}
		status = wait_pipeline(pid);
	}
	g_data.last_status = status;
}
