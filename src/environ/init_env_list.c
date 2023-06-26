/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:06:49 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 16:20:06 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env_list(char **envp)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		set_env_list(&env, envp[i]);
		i++;
	}
	return (env);
}
