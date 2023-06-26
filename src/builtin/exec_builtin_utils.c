/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 05:56:27 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 05:56:49 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_argc(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
		i++;
	return (i);
}

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
