/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:41:21 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 03:37:07 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

static int	free_env_next(t_env **env, t_env *current)
{
	*env = current->next;
	free_env(current);
	return (0);
}

static int	check_env_list(char **key, t_env **current)
{
	if (*key == NULL || !is_variable(*key))
		return (-1);
	*current = NULL;
	return (0);
}

int	unset_env_list(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*current;

	if (check_env_list(&key, &current))
		return (-1);
	if (*env != NULL)
	{
		current = *env;
		if (ft_strcmp(current->key, key) == 0)
			return (free_env_next(env, current));
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
	return (0);
}
