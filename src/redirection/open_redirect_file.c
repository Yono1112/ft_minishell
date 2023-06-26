/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirect_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:12:17 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 01:12:26 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_node **node, t_env **env)
{
	if ((*node)->kind == ND_PIPELINE)
	{
		(*node) = (*node)->command;
		return (0);
	}
	else if ((*node)->kind == ND_SIMPLE_CMD)
	{
		(*node) = (*node)->redirects;
		return (0);
	}
	else if ((*node)->kind == ND_REDIR_OUT)
		(*node)->filefd = open(
				(*node)->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if ((*node)->kind == ND_REDIR_IN)
		(*node)->filefd = open((*node)->filename->word, O_RDONLY);
	else if ((*node)->kind == ND_REDIR_APPEND)
		(*node)->filefd = open(
				(*node)->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if ((*node)->kind == ND_REDIR_HEREDOC)
		(*node)->filefd = read_heredoc((*node)->delimiter->word,
				(*node)->is_delimiter_quote, env);
	else
		fatal_error("open_redirect_file");
	return (1);
}

int	open_redirect_file(t_node *node, t_env **env)
{
	t_node	*start_node;

	start_node = node;
	while (node != NULL)
	{
		if (!open_file(&node, env))
			continue ;
		if (node->filefd < 0)
		{
			if (node->kind == ND_REDIR_IN
				|| node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_APPEND)
			{
				write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
				perror(node->filename->word);
			}
			return (-1);
		}
		node->filefd = stashfd(node->filefd);
		node = node->next;
	}
	if (start_node->next != NULL && start_node->next->kind == ND_PIPELINE)
		open_redirect_file(start_node->next, env);
	return (0);
}
