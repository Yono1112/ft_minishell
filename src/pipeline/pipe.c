/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:09:12 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/17 20:58:21 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	cpy_pipe(int dst[2], int src[2])
// {
// 	dst[0] = src[0];
// 	dst[1] = src[1];
// }
// 
// void	prepare_pipe(t_node *node)
// {
// 	if (node->next == NULL)
// 		return ;
// 	if (pipe(node->outpipe) < 0)
// 		fatal_error("pipe");
// 	printf("node->outpipe[0]: %d, node->outpipe[1]: %d\n", node->outpipe[0], node->outpipe[1]);
// 	cpy_pipe(node->next->inpipe, node->outpipe);
// 	printf("node->inpipe[0]: %d, node->inpipe[1]: %d\n", node->next->inpipe[0], node->next->inpipe[1]);
// }

void	prepare_pipe(t_node *node)
{
	if (node->next != NULL)
	{
		if (pipe(node->outpipe) < 0)	
			fatal_error("pipe");
		// printf("node->outpipe[0]: %d, node->outpipe[1]: %d\n", node->outpipe[0], node->outpipe[1]);
		node->next->inpipe[0] = node->outpipe[0];
		node->next->inpipe[1] = node->outpipe[1];
		// printf("node->inpipe[0]: %d, node->inpipe[1]: %d\n", node->next->inpipe[0], node->next->inpipe[1]);
	}
}

void	prepare_pipe_child(t_node *node)
{
	close(node->outpipe[0]);
	dup2(node->inpipe[0], STDIN_FILENO);
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	dup2(node->outpipe[1], STDOUT_FILENO);
	if (node->outpipe[1] != STDOUT_FILENO)
		close(node->outpipe[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		close(node->inpipe[0]);
	if (node->next)
		close(node->outpipe[1]);
}
