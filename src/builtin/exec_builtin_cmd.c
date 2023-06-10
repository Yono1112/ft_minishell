/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:33:42 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/07 20:43:07 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_cmd(t_node *node)
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
	if (strcmp(argv[0], "exit") == 0)
	{
		// printf("exit\n");
		status = exec_builtin_exit(argv);
	}
	else if (strcmp(argv[0], "echo") == 0)
	{
		// printf("echo\n");
		status = exec_builtin_echo(argv);
	}
	else
		todo("exec_builtin");
	free_argv(argv);
	reset_redirect(node->command->redirects);
	return (status);
}
