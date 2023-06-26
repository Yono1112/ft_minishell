/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:14:09 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 01:14:19 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_redirect(t_node *redirect)
{
	if (redirect == NULL)
		return ;
	reset_redirect(redirect->next);
	if (is_redirect(redirect))
	{
		if (dup2(redirect->stashed_targetfd, redirect->targetfd) < 0)
		{
			fatal_error("dup2");
			return ;
		}
	}
	else
		fatal_error("reset_redirect");
}
