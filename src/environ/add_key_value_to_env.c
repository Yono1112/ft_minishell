/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_key_value_to_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:08:43 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 05:14:57 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_key_value_to_env(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*last_env;

	if (value == NULL)
	{
		new_env = create_new_env_list(ft_strdup(key), NULL);
		if (new_env->key == NULL)
			fatal_error("ft_strdup");
	}
	else
	{
		new_env = create_new_env_list(ft_strdup(key), ft_strdup(value));
		if (new_env->key == NULL || new_env->value == NULL)
			fatal_error("ft_strdup");
	}
	if (*env == NULL)
		*env = new_env;
	else
	{
		last_env = *env;
		while (last_env->next != NULL)
			last_env = last_env->next;
		last_env->next = new_env;
	}
}
