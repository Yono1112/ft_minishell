/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:13:14 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/29 20:52:05 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redirect(t_node *redirect)
{
	while (redirect != NULL)
	{
		if (is_redirect(redirect))
		{
			if (redirect->stashed_std_fd != STDIN_FILENO)
				redirect->stashed_std_fd = stashfd(redirect->std_fd);
			if (redirect->filefd > 0
				&& dup2(redirect->filefd, redirect->std_fd) < 0)
			{
				fatal_error("dup2");
				return ;
			}
			close(redirect->filefd);
		}
		else
			fatal_error("do_redirect");
		redirect = redirect->next;
	}
}
