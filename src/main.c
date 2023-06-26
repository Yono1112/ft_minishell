/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 12:35:16 by yuohno           ###   ########.fr       */
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

t_data	g_data;

void	print_token(t_token *token)
{
	while (token && token->kind != TK_EOF)
	{
		printf("token_word: %s\n", token->word);
		token = token->next;
	}
}

void	print_env(t_env *env)
{
	printf("start print_env\n");
	printf("=======================================================\n");
	while (env)
	{
		printf("env->key:%s, env->value:%s\n", env->key, env->value);
		env = env->next;
	}
}

void	init_g_data(void)
{
	g_data.last_status = 0;
	// g_data.syntax_error = false;
	g_data.readline_interrupted = false;
	g_data.sig = 0;
	// g_data._rl_echo_control_chars = NOT_CONTROL_CHARS;
}

void	interpret(char* const line, int *status, t_env **env)
{
	t_token	*token;
	t_node	*node;
	int		syntax_error;

	syntax_error = 0;
	token = tokenize(line, &syntax_error);
	// printf("syntax_error:%d\n", syntax_error);
	if (token->kind != TK_EOF && syntax_error)
		*status = ERROR_TOKENIZE;
	else if (token->kind != TK_EOF)
	{
		node = parse(token, &syntax_error);
		if (syntax_error)
			*status = ERROR_PARSE;
		else
		{
			expand(node, env);
			*status = exec(node, env);
		}
		free_node(node);
	}
	// print_token(token);
	free_token(token);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	// print_envp(envp);
	// printf("-------------------------------------------\n");
	env = init_env_list(envp);
	init_g_data();
	// print_env(env);
	// set_env_list(&env, "USER=rnaka", true);
	// printf("-------------------------------------------\n");
	// print_env(env);
	// printf("-------------------------------------------\n");
	// set_env_list(&env, "USER", true);
	// print_env(env);
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
		interpret(line, &g_data.last_status, &env);
		if (line)
			free(line);
	}
	exit (g_data.last_status);
}
