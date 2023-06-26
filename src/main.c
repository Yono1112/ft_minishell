/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 05:53:05 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

// void	print_argv(char **str)
// {
// 	int	i = 0;

// 	while (str[i])
// 	{
// 		printf("str[%d]:%s\n", i, str[i]);
// 		i++;
// 	}
// }

// void	print_token(t_token *token)
// {
// 	while (token && token->kind != TK_EOF)
// 	{
// 		printf("token_word: %s\n", token->word);
// 		token = token->next;
// 	}
// }

// void	print_env(t_env *env)
// {
// 	printf("start print_env\n");
// 	printf("=======================================================\n");
// 	while (env)
// 	{
// 		printf("env->key:%s, env->value:%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }

// void	print_node(t_node *node)
// {
// 	if (node->command->args)
// 	{
// 		printf("node->command->args\n");
// 		print_token(node->command->args);
// 	}
// 	if (node->command->redirects)
// 	{
// 		printf("node->command->redirects\n");
// 		print_token(node->command->args);
// 		print_token(node->command->redirects->filename);
// 		print_token(node->command->redirects->delimiter);
// 	}
// 	if (node->next)
// 		print_node(node->next);
// }

void	init_g_data(void)
{
	g_data.last_status = 0;
	g_data.readline_interrupted = false;
	g_data.sig = 0;
}

void	interpret(char *const line, int *status, t_env **env)
{
	t_token	*token;
	t_node	*node;
	int		syntax_error;

	syntax_error = 0;
	token = tokenize(line, &syntax_error);
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
	free_token(token);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	env = init_env_list(envp);
	init_g_data();
	set_signal();
	while (1)
	{
		line = readline(SHELL_PROMPT);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_data.last_status, &env);
		if (line)
			free(line);
	}
	exit (g_data.last_status);
}
