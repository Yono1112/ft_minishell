/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:41:21 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/23 00:35:04 by yumaohno         ###   ########.fr       */
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
		if (strcmp(current->key, key) == 0)
		{
			*env = current->next;
			free_env(current);
		}
		current = current->next;
		prev = *env;
		while (current)
		{
			if (strcmp(current->key, key) == 0)
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