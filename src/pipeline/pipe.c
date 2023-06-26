/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:09:12 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 17:05:09 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_pipe(t_node *node)
{
	if (node->next != NULL)
	{
		if (pipe(node->outpipe) < 0)	
			fatal_error("pipe");
		node->next->inpipe[0] = node->outpipe[0];
		node->next->inpipe[1] = node->outpipe[1];
	}
}

void	prepare_pipe_child(t_node *node)
{
	if (node->next != NULL)
	{
		dup2(node->outpipe[1], STDOUT_FILENO);
		if (node->outpipe[1] != STDOUT_FILENO)
			close(node->outpipe[1]);
	}
	dup2(node->inpipe[0], STDIN_FILENO);
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	close(node->outpipe[0]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->next != NULL)
	  	close(node->outpipe[1]);
	if (node->inpipe[0] != STDIN_FILENO)
	 	close(node->inpipe[0]);
}
