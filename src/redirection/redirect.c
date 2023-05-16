/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:27:15 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/16 17:47:02 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	stashfd(int fd)
{
	int		stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	printf("stashfd: %d\n", stashfd);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

int	open_redirect_file(t_node *node)
{
	printf("start open_redirect\n");
	while (node != NULL)
	{
		printf("node_kind: %d\n", node->kind);
		if (node->kind == ND_PIPELINE)
		{
			node = node->command;
			printf("node_kind is ND_PIPELINE\n");
			continue ;
		}
		else if (node->kind == ND_SIMPLE_CMD)
		{
			node = node->redirects;
			printf("node_kind is ND_SIMPLE_CMD\n");
			continue ;
		}
		else if (node->kind == ND_REDIR_OUT)
		{
			printf("redirect_out\n");
			node->filefd = open(node->filename->word,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			printf("node_filefd: %d\n", node->filefd);
		}
		else if (node->kind == ND_REDIR_IN)
		{
			printf("redirect_in\n");
			node->filefd = open(node->filename->word, O_RDONLY);
			printf("node_filefd: %d\n", node->filefd);
		}
		else if (node->kind == ND_REDIR_APPEND)
			node->filefd = open(node->filename->word,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (node->kind == ND_REDIR_HEREDOC)
			node->filefd = read_heredoc(node->delimiter->word);
		else
			todo("open_node_file");
		if (node->filefd < 0)
		{
			xperror(node->filename->word);
			return (-1);
		}
		node->filefd = stashfd(node->filefd);
		node = node->next;
	}
	printf("finish open_redirect\n");
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
		printf("start do_redirect\n");
		if (is_redirect(redirect))
		{
			printf("redirect_targetfd: %d\n", redirect->targetfd);
			redirect->stashed_targetfd = stashfd(redirect->targetfd);
			if (dup2(redirect->filefd, redirect->targetfd) < 0)
			{
				fatal_error("dup2");
				return ;
			}
			close(redirect->filefd);
		}
		else
			todo("do_redirect");
		redirect = redirect->next;
	}
	printf("finish do_redirect\n");
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
