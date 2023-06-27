/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:33:42 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 15:54:29 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin_cmd_devide_word(char **argv, t_env **env)
{
	int	status;

	status = 0;
	if (ft_strcmp(argv[0], "exit") == 0)
		status = exec_builtin_exit(argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = exec_builtin_echo(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = exec_builtin_cd(argv, env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = exec_builtin_pwd(argv, env);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = exec_builtin_export(argv, env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = exec_builtin_unset(argv, env);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = exec_builtin_env(env);
	else
		fatal_error("exec_builtin_cmd");
	return (status);
}

int	exec_builtin_cmd(t_node *node, t_env **env)
{
	int		status;
	char	**argv;

	status = 0;
	argv = NULL;
	reset_signal_to_default();
	prepare_pipe_child(node);
	if (node->command->redirects != NULL)
		do_redirect(node->command->redirects);
	if (node->command->args != NULL)
		argv = add_token_to_argv(node->command->args);
	status = exec_builtin_cmd_devide_word(argv, env);
	free_argv(argv);
	reset_redirect(node->command->redirects);
	return (status);
}
