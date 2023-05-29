/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/29 16:21:31 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <string.h>
// #include <limits.h>
// #include <readline/history.h>

int	last_status;

void	interpret(char* const line, int *status)
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
	char		*line;

	rl_outstream = stderr;
	last_status = 0;
	set_signal();
	// signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			// printf("Ctrl + D\n");
			break ;
		}
		if (*line)
			add_history(line);
		interpret(line, &last_status);
		free(line);
	}
	exit (last_status);
}
