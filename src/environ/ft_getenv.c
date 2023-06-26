/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:09:54 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 16:19:57 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *path_key, t_env **env)
{
	t_env *current;

	current = *env;
	if (path_key == NULL)
		return (NULL);
	while (current != NULL)
	{
		if (ft_strcmp(current->key, path_key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
