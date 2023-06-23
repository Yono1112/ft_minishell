/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:40:13 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 02:11:41 by yumaohno         ###   ########.fr       */
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

	// env = calloc(1, sizeof(*env));
	env = calloc(1, sizeof(*env));
	if (env == NULL)
		fatal_error("calloc");
	env->key = key;
	env->value = value;
	return (env);
}
