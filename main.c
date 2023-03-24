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

#include <minishell.h>

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
		{
			path_len = (size_t)end - (size_t)value;
			if (path_len >= PATH_MAX)
			{
				fprintf(stderr, "Error: PATH element is too long\n");
				return (NULL);
			}
			memcpy(path, value, path_len);
			path[path_len] = '\0';
		}
		else
		{
			path_len = strlen(value);
			if (path_len >= PATH_MAX)
			{
				fprintf(stderr, "Error: PATH element is too long\n");
				return (NULL);
			}
			strcpy(path, value);
		}
		path_len = strlen(path);
		strncat(path, "/", PATH_MAX - path_len - 1);
		strncat(path, filename, PATH_MAX - path_len - 1);
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

int	exec_cmd(char *argv[])
{
	extern char	**environ;
	const char	*path = argv[0];
	pid_t		pid;
	int			wstatus;

	// if run execve in parent process
	// execve(line, argv, environ);
	// printf("aaaa");
	// return (0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork Error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (strchr(path, '/') == NULL)
			path = check_cmd_path(path);
		if (!check_is_filename(path))
		{
			exit(EXIT_FAILURE);
		}
		execve(path, argv, environ);
		perror("execve Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		pid = wait(&wstatus);
		if (pid == -1)
		{
			perror("wait error");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(wstatus))
		{
			// printf("Child process exited with status %d\n",
				// WEXITSTATUS(wstatus));
			return (WEXITSTATUS(wstatus));
		}
		else
		{
			// printf("Child process exited abnormally\n");
			return (WEXITSTATUS(wstatus));
		}
	}
}

int	interpret(char *const line)
{
	int	status;
	char	*argv[] = {line, NULL};

	status = exec_cmd(argv);
	return (status);
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
		status = interpret(line);
		free(line);
	}
	exit (status);
}
