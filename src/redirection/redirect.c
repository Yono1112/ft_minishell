/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:27:15 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/07 16:18:20 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	stashfd(int fd)
{
	int		stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	// printf("stashfd: %d\n", stashfd);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

void	open_redirect_file(t_node *redirect)
{
	// printf("yes\n");
	if (redirect == NULL)
	{
		// printf("no\n");
		return ;
	}
	if (redirect->kind == ND_REDIR_OUT)
	{
		// printf("open\n");
		redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
		todo("open_redirect_file");
	// printf("open_stashfd\n");
	redirect->filefd = stashfd(redirect->filefd);
	open_redirect_file(redirect->next);
}

void	do_redirect(t_node *redirect)
{
	if (redirect == NULL)
	{
		// printf("do\n");
		return ;
	}
	if (redirect->kind == ND_REDIR_OUT)
	{
		// printf("do_stashfd\n");
		redirect->stashed_targetfd = stashfd(redirect->targetfd);
		dup2(redirect->filefd, redirect->targetfd);
	}
	do_redirect(redirect->next);
}

void	reset_redirect(t_node *redirect)
{
	if (redirect == NULL)
	{
		// printf("reset\n");
		return ;
	}
	reset_redirect(redirect->next);
	if (redirect->kind == ND_REDIR_OUT)
	{
		close(redirect->filefd);
		close(redirect->targetfd);
		dup2(redirect->stashed_targetfd, redirect->targetfd);
	}
}
