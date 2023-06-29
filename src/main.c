/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/29 11:50:26 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

static void	init_g_data(void)
{
	g_data.last_status = 0;
	g_data.heredoc_sig_received = false;
	g_data.sig = 0;
}

static void	process_input(char *const line, t_env **env)
{
	t_token	*token;
	t_node	*node;
	int		syntax_error;

	syntax_error = 0;
	token = tokenize(line, &syntax_error);
	if (token->kind != TK_EOF && syntax_error)
		g_data.last_status = ERROR_TOKENIZE;
	else if (token->kind != TK_EOF)
	{
		node = parse(token, &syntax_error);
		if (syntax_error)
			g_data.last_status = ERROR_PARSE;
		else
		{
			expand(node, env);
			exec(node, env);
		}
		free_node(node);
	}
	free_token(token);
}

static void	input_readline(t_env **env)
{
	char	*input;

	while (1)
	{
		input = readline(SHELL_PROMPT);
		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "exit\n", ft_strlen("exit\n"));
			break ;
		}
		if (*input)
			add_history(input);
		process_input(input, env);
		if (input)
			free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	env = init_env_list(envp);
	init_g_data();
	set_signal();
	input_readline(&env);
	exit (g_data.last_status);
}
