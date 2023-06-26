/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:33:42 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/26 13:20:25 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_cmd(t_node *node, t_env **env)
{
	int		status;
	char	**argv;

	// printf("start exec_builtin_cmd\n");
	status = 0;
	argv = NULL;
	if (node->command->redirects != NULL)
		do_redirect(node->command->redirects);
	if (node->command->args != NULL)
	{
		// printf("start add_token_to_argv\n");
		argv = add_token_to_argv(node->command->args);
	}
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		// printf("exit\n");
		status = exec_builtin_exit(argv);
	}
	else if (ft_strcmp(argv[0], "echo") == 0)
	{
		// printf("echo\n");
		status = exec_builtin_echo(argv);
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
	{
		status = exec_builtin_cd(argv, env);
	}
	else if (ft_strcmp(argv[0], "pwd") == 0)
	{
		status = exec_builtin_pwd(argv, env);
	}
	else if (ft_strcmp(argv[0], "export") == 0)
	{
		// printf("export\n");
		// printf("print_env before export\n");
		// print_env(env);
		// set_env_list(&env, "USER=", true);
		// printf("print_env after export\n");
		// print_env(env);
		status = exec_builtin_export(argv, env);
	}
	else if (ft_strcmp(argv[0], "unset") == 0)
	{
		// printf("unset\n");
		status = exec_builtin_unset(argv, env);
	}
	else if (ft_strcmp(argv[0], "env") == 0)
	{
		// printf("env\n");
		// print_env(env);
		status = exec_builtin_env(env);
	}
	else
		fatal_error("exec_builtin_cmd");
	free_argv(argv);
	reset_redirect(node->command->redirects);
	return (status);
}
