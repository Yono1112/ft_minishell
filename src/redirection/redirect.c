/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:27:15 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/25 03:49:20 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

bool	readline_interrupted = false;

static int	stashfd(int fd)
{
	int		stashfd;

	// printf("start stashfd\n");
	// printf("fd in stashfd: %d\n", fd);
	stashfd = fcntl(fd, F_DUPFD, 10);
	// printf("stashfd in stashfd: %d\n", stashfd);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	// printf("finish stashfd\n");
	return (stashfd);
}

int	read_heredoc(const char *delimiter, bool is_delimiter_quote, t_env **env)
{
	char	*line;
	int		pfd[2];

	// printf("delimiter: %s\n", delimiter);
	// printf("is_delimiter_quote: %d\n", is_delimiter_quote);
	if (pipe(pfd) < 0)
		fatal_error("pipe");
	// printf("pfd[0]: %d\n", pfd[0]);
	// printf("pfd[1]: %d\n", pfd[1]);
	readline_interrupted = false;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (readline_interrupted || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (is_delimiter_quote)
			line = expand_heredoc_line(line, env);
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	if (readline_interrupted)
	{
		close(pfd[0]);
		return (-1);
	}
	close(pfd[1]);
	return (pfd[0]);
}

int	open_redirect_file(t_node *node, t_env **env)
{
	// printf("start open_redirect\n");
	t_node *start_node;

	start_node = node;
	while (node != NULL)
	{
		if (node->kind == ND_PIPELINE)
		{
			// printf("node_kind is ND_PIPELINE\n");
			node = node->command;
			continue ;
		}
		else if (node->kind == ND_SIMPLE_CMD)
		{
			// printf("node_kind is ND_SIMPLE_CMD\n");
			node = node->redirects;
			continue ;
		}
		else if (node->kind == ND_REDIR_OUT)
		{
			// printf("out\n");
			node->filefd = open(node->filename->word,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			// printf("node_kind is ND_REDIR_OUT, filefd: %d\n", node->filefd);
		}
		else if (node->kind == ND_REDIR_IN)
		{
			// printf("in\n");
			node->filefd = open(node->filename->word, O_RDONLY);
			// printf("node_kind is ND_REDIR_IN, filefd: %d\n", node->filefd);
		}
		else if (node->kind == ND_REDIR_APPEND)
		{
			// printf("append\n");
			node->filefd = open(node->filename->word,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			// printf("node_kind is ND_REDIR_APPEND, filefd: %d\n", node->filefd);
		}
		else if (node->kind == ND_REDIR_HEREDOC)
		{
			// printf("heredoc\n");
			node->filefd = read_heredoc(node->delimiter->word, node->is_delimiter_quote, env);
			// printf("node_kind is ND_REDIR_HEREDOC, filefd: %d\n", node->filefd);
		}
		else
			todo("open_node_file");
		if (node->filefd < 0)
		{
			if (node->kind == ND_REDIR_IN || node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_APPEND)
				xperror(node->filename->word);
			return (-1);
		}
		node->filefd = stashfd(node->filefd);
		// printf("node->filefd after stashfd: %d\n", node->filefd);
		// printf("open_redirect next node\n");
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
		// printf("start do_redirect\n");
		if (is_redirect(redirect))
		{
			// printf("redirect->targetfd: %d\n", redirect->targetfd);
			if (redirect->stashed_targetfd != STDIN_FILENO)
				redirect->stashed_targetfd = stashfd(redirect->targetfd);
			// printf("redirect->stashed_targetfd: %d\n", redirect->stashed_targetfd);
			if (dup2(redirect->filefd, redirect->targetfd) < 0)
			{
				fatal_error("dup2");
				return ;
			}
			close(redirect->filefd);
			// printf("redirect->filefd after dup2: %d\n", redirect->filefd);
		}
		else
			todo("do_redirect");
		redirect = redirect->next;
	}
	// printf("finish do_redirect\n");
}

void	reset_redirect(t_node *redirect)
{
	if (redirect == NULL)
		return ;
	reset_redirect(redirect->next);
	if (is_redirect(redirect))
	{
		// close(redirect->filefd);
		// close(redirect->targetfd);
		if (dup2(redirect->stashed_targetfd, redirect->targetfd) < 0)
		{
			fatal_error("dup2");
			return ;
		}
	}
	else
		todo("rest_redirect");
}

// int	open_redirect_file(t_node *redirect)
// {
// 	if (redirect == NULL)
// 		return (0);
// 	if (redirect->kind == ND_REDIR_OUT)
// 		redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else if (redirect->kind == ND_REDIR_IN)
// 		redirect->filefd = open(redirect->filename->word, O_RDONLY);
// 	else if (redirect->kind == ND_REDIR_APPEND)
// 		redirect->filefd = open(redirect->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	else
// 		todo("open_redirect_file");
// 	if (redirect->filefd < 0)
// 	{
// 		xperror(redirect->filename->word);
// 		return (-1);
// 	}
// 	redirect->filefd = stashfd(redirect->filefd);
// 	return (open_redirect_file(redirect->next));
// }

// void	do_redirect(t_node *redirect)
// {
// 	if (redirect == NULL)
// 	{
// 		// printf("do\n");
// 		return ;
// 	}
// 	printf("do_not_null\n");
// 	if (redirect->kind == ND_REDIR_OUT || redirect->kind == ND_REDIR_IN)
// 	{
// 		printf("do_stashfd\n");
// 		redirect->stashed_targetfd = stashfd(redirect->targetfd);
// 		if (dup2(redirect->filefd, redirect->targetfd) < 0)
// 		{
// 			printf("do_no!\n");
// 			xperror("dup2");
// 			return ;
// 		}
// 		else
// 			printf("do_yes\n");
// 	}
// 	else
// 	{
// 		printf("do_todo\n");
// 		todo("do_redirect");
// 	}
// 	do_redirect(redirect->next);
// }

// void	reset_redirect(t_node *redirect)
// {
// 	t_node	*current;

// 	current = redirect;
// 	while (current != NULL)
// 	{
// 		if (current->kind == ND_REDIR_OUT)
// 		{
// 			close(current->filefd);
// 			close(current->targetfd);
// 			dup2(current->stashed_targetfd, current->targetfd);
// 		}
// 		current = current->next;
// 	}
// }
