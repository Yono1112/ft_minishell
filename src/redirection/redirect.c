/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:27:15 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 21:44:03 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	ft_fcntl(int fd)
{
	int		stashed_fd;
	int		target_fd;
	struct stat	stat;

	target_fd = 10;
	errno = 0;
	if (fd < 0)
	{
		errno = EBADF;
		return (-1);
	}
	while (!fstat(target_fd, &stat) && errno != EBADF)
		target_fd++;
	stashed_fd = dup2(fd,target_fd);
	return (stashed_fd);
}

static int	stashfd(int fd)
{
	int		stashfd;

	stashfd = ft_fcntl(fd);
	if (stashfd < 0)
		fatal_error("ft_fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

static void	while_read_heredoc(const char *delimiter,
				bool is_delimiter_quote, t_env **env, int *pfd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_data.readline_interrupted || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (is_delimiter_quote)
			line = expand_heredoc_line(line, env);
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], NEW_LINE, ft_strlen(NEW_LINE));
		free(line);
	}
}

int	read_heredoc(const char *delimiter, bool is_delimiter_quote, t_env **env)
{
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while_read_heredoc(delimiter, is_delimiter_quote, env, pfd);
	if (g_data.readline_interrupted)
	{
		close(pfd[0]);
		return (-1);
	}
	close(pfd[1]);
	return (pfd[0]);
}

static int open_file(t_node **node, t_env **env)
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
		(*node)->filefd = open((*node)->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if ((*node)->kind == ND_REDIR_IN)
		(*node)->filefd = open((*node)->filename->word, O_RDONLY);
	else if ((*node)->kind == ND_REDIR_APPEND)
		(*node)->filefd = open((*node)->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if ((*node)->kind == ND_REDIR_HEREDOC)
		(*node)->filefd = read_heredoc((*node)->delimiter->word, (*node)->is_delimiter_quote, env);
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

bool	is_redirect(t_node *redirect)
{
	if (redirect->kind == ND_REDIR_IN || redirect->kind == ND_REDIR_OUT
		|| redirect->kind == ND_REDIR_APPEND
		|| redirect->kind == ND_REDIR_HEREDOC)
		return (true);
	else
		return (false);
}

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
