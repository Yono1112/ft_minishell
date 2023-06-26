/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:13:14 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 04:57:43 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redirect(t_node *redirect)
{
	while (redirect != NULL)
	{
		if (is_redirect(redirect))
		{
			if (redirect->stashed_targetfd != STDIN_FILENO)
				redirect->stashed_targetfd = stashfd(redirect->targetfd);
			if (dup2(redirect->filefd, redirect->targetfd) < 0)
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
