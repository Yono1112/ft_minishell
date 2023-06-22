/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:00:07 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 14:59:43 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_environ_variable(t_env **env)
{
	// printf("start print_environ_variable\n");
	// if (env == NULL)
	// 	printf("env is NULL\n");
	while (*env != NULL)
	{
		if ((*env)->value != NULL)
			printf("declare -x %s=\"%s\"\n", (*env)->key, (*env)->value);
		else
			printf("declare -x %s\n", (*env)->key);
		(*env) = (*env)->next;
	}
	// printf("finish print_environ_variable\n");
}

int	exec_builtin_export(char **argv, t_env **env)
{
	int	argc;
	size_t	i;
	int	status;

	status = 0;
	argc = count_argc(argv);
	if (argc == 1)
		print_environ_variable(env);
	else
	{
		i = 1;
		while (argv[i])
		{
			if (set_env_list(env, argv[i]) == -1 ) 
			{
				builtin_error("export", argv[i], "not a valid identifier");
				status = 1;
			}
			i++;
		}
	}
	// print_env(*env);
	return (status);
}
