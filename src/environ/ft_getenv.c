/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:09:54 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 02:10:02 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *path_key, t_env *env)
{
	if (path_key == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (strcmp(env->key, path_key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
