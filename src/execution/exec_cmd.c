/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:32:26 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 00:41:43 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd_if(t_node **node, t_env **env, pid_t *pid)
{
	int	status;

	status = 0;
	if (*pid < 0)
		fatal_error("fork");
	else if (*pid == CHILD_PID)
	{
		reset_signal_to_default();
		prepare_pipe_child(*node);
		if (is_builtin(*node))
		{
			status = exec_builtin_cmd(*node, env);
			exit(status);
		}
		else
			exec_simple_cmd(*node, env);
	}
	return (status);
}

int	exec_cmd(t_node *node, t_env **env)
{
	pid_t		pid;
	int			status;

	while (node != NULL)
	{
		prepare_pipe(node);
		pid = fork();
		status = exec_cmd_if(&node, env, &pid);
		prepare_pipe_parent(node);
		node = node->next;
	}
	status = wait_pipeline(pid);
	return (status);
}
