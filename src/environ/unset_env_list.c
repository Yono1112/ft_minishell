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

int	unset_env_list(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*current;

	// printf("start unset_env_list\n");
	// print_env(*env);
	if (key == NULL || !is_variable(key))
		return (-1);
	if (*env != NULL)
	{
		prev = *env;
		current = (*env)->next;
		while (current)
		{
			if (strcmp(current->key, key) == 0)
			{
				prev->next = current->next;
				free(current->key);
				free(current->value);
				free(current);
				break ;
			}
			current = current->next;
			prev = prev->next;
		}
	}
	return (0);
}
