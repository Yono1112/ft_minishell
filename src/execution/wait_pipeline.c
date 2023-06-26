/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:35:17 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 00:35:31 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_pipeline_if(int *status, int *wstatus,
		pid_t *wait_pid, pid_t *last_child_pid)
{
	if (*wait_pid == *last_child_pid)
	{
		if (WIFSIGNALED(*wstatus))
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			*status = 128 + WTERMSIG(*wstatus);
		}
		else
			*status = WEXITSTATUS(*wstatus);
	}
}

int	wait_pipeline(pid_t last_child_pid)
{
	pid_t	wait_pid;
	int		status;
	int		wstatus;

	while (1)
	{
		g_data.sig = 0;
		wait_pid = wait(&wstatus);
		if (wait_pid == last_child_pid)
			wait_pipeline_if(&status, &wstatus, &wait_pid, &last_child_pid);
		else if (wait_pid < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}
