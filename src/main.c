/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/06 22:15:28 by yuohno           ###   ########.fr       */
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

void	print_token(t_token *token)
{
	while (token && token->kind != TK_EOF)
	{
		printf("token_word: %s\n", token->word);
		token = token->next;
	}
}

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
	// print_token(token);
	free_token(token);
}

int	main(void)
{
	char		*line;

	rl_outstream = stderr;
	last_status = 0;
	init_env();
	set_signal();
	while (1)
	{
		line = readline(SHELL_PROMPT);
		// line = readline("minishell$ ");
		if (line == NULL)
		{
			// printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		interpret(line, &last_status);
		if (line)
			free(line);
	}
	exit (last_status);
}
