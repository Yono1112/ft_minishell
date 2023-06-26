/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:40:13 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/24 22:41:04 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		printf("envp[%zu]: %s\n", i, envp[i]);
		i++;
	}
}

bool	is_variable(char *str)
{
	size_t	i;

	i = 0;
	if (!is_alpha_under(str[i]))
		return (false);
	i++;
	while (str[i])
	{
		if (!is_alpha_num_under(str[i]))
			return (false);
		i++;
	}
	return (true);
}

t_env	*create_new_env_list(char *key, char *value)
{
	t_env	*env;

	// env = ft_calloc(1, sizeof(*env));
	env = ft_calloc(1, sizeof(*env));
	if (env == NULL)
		fatal_error("ft_calloc");
	env->key = key;
	env->value = value;
	return (env);
}
