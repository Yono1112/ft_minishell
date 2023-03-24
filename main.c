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

int	interpret(char	*line)
{
	extern char	**environ;
	char		*argv[] = {line, NULL};
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
		execve(line, argv, environ);
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
			printf("Child process exited with status %d\n",
				WEXITSTATUS(wstatus));
			return (WEXITSTATUS(wstatus));
		}
		else
		{
			printf("Child process exited abnormally\n");
			return (WEXITSTATUS(wstatus));
		}
	}
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
