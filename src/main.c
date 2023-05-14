/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/24 18:44:57by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <readline/history.h>

bool	check_is_filename(const char *path)
{
	if (path == NULL)
		return (false);
	if (access(path, F_OK) < 0)
		return (false);
	return (true);
}

char	*check_cmd_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;
	size_t	path_len;

	value = getenv("PATH");
	if (!value)
	{
		fprintf(stderr, "Error: PATH environment variable is not set\n");
		return (NULL);
	}
	while (*value)
	{
		end = strchr(value, ':');
		if (end)
			path_len = (size_t)end - (size_t)value;
		else
			path_len = strlen(value);
		if (path_len >= PATH_MAX)
		{
			fprintf(stderr, "Error: PATH element is too long\n");
			return (NULL);
		}
		memcpy(path, value, path_len);
		path[path_len] = '\0';
		strncat(path, "/", PATH_MAX - strlen(path) - 1);
		strncat(path, filename, PATH_MAX - strlen(path) - 1);
		if (access(path, X_OK) == 0)
		{
			dup = strdup(path);
			if (!dup)
			{
				fprintf(stderr, "Error: %s\n", strerror(errno));
				return (NULL);
			}
			return (dup);
		}
		if (end == NULL)
			break ;
		value = end + 1;
	}
	return (NULL);
}

pid_t	exec_cmd(t_node *node)
{
	extern char	**environ;
	char		*path;
	pid_t		pid;
	// int			wstatus;
	char		**argv;

	if (node == NULL)
		return (-1);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == CHILD_PID)
	{
		prepare_pipe_child(node);
		do_redirect(node->command->redirects);
		argv = add_token_to_argv(node->command->args);
		path = argv[0];
		if (strchr(path, '/') == NULL)
			path = check_cmd_path(path);
		if (!check_is_filename(path))
			err_exit(argv[0], "command not found", 127);
		execve(path, argv, environ);
		perror("execve Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		prepare_pipe_parent(node);
		if (node->next)
			return (exec_cmd(node->next));
		// pid = wait(&wstatus);
		// if (pid == -1)
		// {
		// 	perror("wait error");
		// 	exit(EXIT_FAILURE);
		// }
		// if (WIFEXITED(wstatus))
		// {
		// 	// printf("Child process exited with status %d\n",
		// 	// 	WEXITSTATUS(wstatus));
		// 	return (WEXITSTATUS(wstatus));
		// }
		// else
		// {
		// 	// printf("Child process exited abnormally\n");
		// 	return (WEXITSTATUS(wstatus));
		// }
	}
	return (pid);
}

int	wait_pipeline(pid_t last_child_pid)
{
	pid_t	wait_pid;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_pid = wait(&wstatus);
		if (wait_pid == last_child_pid)
			status = WEXITSTATUS(wstatus);
		else if (wait_pid < 0)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	return (status);
}

int	exec(t_node *node)
{
	int		status;
	pid_t	last_child_pid;

	if (open_redirect_file(node->redirects) < 0)
		return (ERROR_OPEN_REDIR);
	last_child_pid = exec_cmd(node);
	status = wait_pipeline(last_child_pid);
	// reset_redirect(node->redirects);
	return (status);
}

void	interpret(char *const line, int *status)
{
	t_token	*token;
	t_node	*node;

	token = tokenize(line);
	if (token->kind != TK_EOF && syntax_error)
		*status = ERROR_TOKENIZE;
	else if (token->kind != TK_EOF)
	{
		node = parse(token);
		if (syntax_error)
			*status = ERROR_PARSE;
		else
		{
			expand(node);
			*status = exec(node);
		}
		free_node(node);
	}
	free_token(token);
}

int	main(void)
{
	char	*line;
	int		status;

	status = 0;
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &status);
		free(line);
	}
	exit (status);
}
