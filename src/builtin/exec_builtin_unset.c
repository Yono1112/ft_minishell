/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:36:26 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 23:36:31 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_unset(char **argv, t_env **env)
{
	size_t	i;
	int	status;

	// printf("start exec_builtin_unset\n");
	i = 1;
	status = 0;
	// print_env(*env);
	while (argv[i])
	{
		if (unset_env_list(env, argv[i]) == -1)
		{
			builtin_error("unset", argv[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	// print_env(*env);
	return (status);
}
