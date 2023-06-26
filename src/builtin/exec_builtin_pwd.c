/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:49:15 by rnaka             #+#    #+#             */
/*   Updated: 2023/06/27 03:37:30 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cwd(t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		if (!ft_getenv("PWD", env))
			add_key_value_to_env(env, "PWD", cwd);
		else
			update_value_to_env(env, "PWD", cwd);
		free(cwd);
		return (0);
	}
	return (1);
}

int	exec_builtin_pwd(char **argv, t_env **env)
{
	char	*cwd;

	(void)argv;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		if (!ft_getenv("PWD", env))
			add_key_value_to_env(env, "PWD", cwd);
		else
			update_value_to_env(env, "PWD", cwd);
		free(cwd);
		return (0);
	}
	free(cwd);
	return (1);
}
