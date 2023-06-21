/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:06:49 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 02:06:58 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env_list(char **envp)
{
	t_env	*env;
	size_t	i;

	// printf("start create_env_list\n");
	// print_envp(envp);
	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		// printf("===============================\n");
	 	// printf("envp[%zu]: %s\n", i, envp[i]);
		set_env_list(&env, envp[i], false);
		// printf("env->key:%s, env->value:%s\n", env->key, env->value);
		i++;
	}
	return (env);
}