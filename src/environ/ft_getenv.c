/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:09:54 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 14:58:27 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *path_key, t_env **env)
{
	t_env *current;

	// print_env(*env);
	current = *env;
	if (path_key == NULL)
		return (NULL);
	while (current != NULL)
	{
		if (strcmp(current->key, path_key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
