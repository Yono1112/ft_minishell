/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:15:21 by rnaka             #+#    #+#             */
/*   Updated: 2023/06/27 05:59:26 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<limits.h>
#include <errno.h>
#include"minishell.h"

int	output_cd_argv_error(char *str)
{
	if (access(str, F_OK) < 0)
		builtin_error("cd", str, "no such file or directory");
	else if (access(str, X_OK) < 0)
		builtin_error("cd", str, "permission denied");
	return (1);
}

static int	cd_argv(char **argv, t_env **env)
{
	int		status;
	char	*save;
	char	*cwd;

	status = chdir(argv[1]);
	if (status)
		return (output_cd_argv_error(argv[1]));
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	save = ft_strdup(ft_getenv("PWD", env));
	if (!save)
		return (1);
	update_value_to_env(env, "PWD", cwd);
	if (!ft_getenv("OLDPWD", env))
		add_key_value_to_env(env, "OLDPWD", save);
	else
		update_value_to_env(env, "OLDPWD", save);
	free(cwd);
	free(save);
	return (status);
}

static int	cd_home(t_env **env)
{
	int		status;
	char	*arg;
	char	*save;

	arg = ft_getenv("HOME", env);
	if (!arg)
	{
		builtin_error("cd", NULL, "HOME not set");
		return (1);
	}
	status = chdir(arg);
	if (status)
	{
		builtin_error("cd", arg, NULL);
		return (1);
	}
	save = ft_strdup(ft_getenv("HOME", env));
	update_value_to_env(env, "PWD", save);
	free(save);
	return (status);
}

static int	cd_prev(t_env **env)
{
	int		status;
	char	*save;

	status = 0;
	if (!ft_getenv("OLDPWD", env))
	{
		builtin_error("cd", NULL, "OLDPWD not set");
		return (1);
	}
	status = chdir(ft_getenv("OLDPWD", env));
	if (status)
	{
		builtin_error("cd", NULL, NULL);
		return (1);
	}
	save = ft_strdup(ft_getenv("OLDPWD", env));
	update_value_to_env(env, "OLDPWD", ft_getenv("PWD", env));
	update_value_to_env(env, "PWD", save);
	free(save);
	return (status);
}

int	exec_builtin_cd(char **argv, t_env **env)
{
	int	argc;

	get_cwd(env);
	argc = count_argc(argv);
	if (argc == 1)
		return (cd_home(env));
	else if (!ft_strcmp(argv[1], "-"))
		return (cd_prev(env));
	return (cd_argv(argv, env));
}
