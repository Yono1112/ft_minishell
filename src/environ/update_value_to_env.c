/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_value_to_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:08:43 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 05:15:07 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_value_to_env(t_env **env, char *key, char *value)
{
	t_env	*update_env;

	if (value == NULL)
		return ;
	update_env = *env;
	while (update_env)
	{
		if (ft_strcmp(update_env->key, key) == 0)
			break ;
		update_env = update_env->next;
	}
	free(update_env->value);
	update_env->value = ft_strdup(value);
	if (update_env->value == NULL)
		fatal_error("ft_strdup");
}
