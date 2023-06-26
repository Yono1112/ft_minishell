/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:41:21 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/25 01:11:02 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

int	unset_env_list(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*current;

	// printf("start unset_env_list\n");
	// print_env(*env);
	if (key == NULL || !is_variable(key))
		return (-1);
	current = NULL;
	if (*env != NULL)
	{
		current = *env;
		if (ft_strcmp(current->key, key) == 0)
		{
			*env = current->next;
			free_env(current);
			return (0);
		}
		current = current->next;
		prev = *env;
		while (current)
		{
			if (ft_strcmp(current->key, key) == 0)
			{
				prev->next = current->next;
				free_env(current);
				break ;
			}
			current = current->next;
			prev = prev->next;
		}
	}
	// print_env(*env);
	return (0);
}
