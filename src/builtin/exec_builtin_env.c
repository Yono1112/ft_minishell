/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 04:20:46 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/23 04:21:53 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_env(t_env **env)
{
	t_env	*current;

	current = NULL;
	if (*env != NULL)
	{
		current = *env;
		while (current != NULL)
		{
			if (current->value != NULL)
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
	}
	return (0);
}
