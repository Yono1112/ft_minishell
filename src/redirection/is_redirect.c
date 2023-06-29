/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:27:36 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 01:28:31 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_node *redirect)
{
	if (redirect->kind == ND_REDIR_IN || redirect->kind == ND_REDIR_OUT
		|| redirect->kind == ND_REDIR_APPEND
		|| redirect->kind == ND_REDIR_HEREDOC)
		return (true);
	else
		return (false);
}
