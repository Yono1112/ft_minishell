/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/24 07:18:44 by yuohno           ###   ########.fr       */
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

int	last_status = 0;

void	print_token(t_token *token)
{
	while (token && token->kind != TK_EOF)
	{
		printf("token_word: %s\n", token->word);
		printf("token->is_expanded: %d\n", token->is_expanded);
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

void	interpret(char* const line, int *status, t_env **env)
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
		interpret(line, &last_status, &env);
		if (line)
			free(line);
	}
	exit (last_status);
}
