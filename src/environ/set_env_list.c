/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:08:43 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 05:15:36 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_key_in_env(char *key, t_env *env)
{
	if (env == NULL || env->key == NULL)
		return (false);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

int	free_key_and_value(char *key, char *value)
{
	free(key);
	free(value);
	return (-1);
}

void	set_env_list_if(char **end_key, char **key, char **str, char **value)
{
	*end_key = ft_strchr(*str, '=');
	if (*end_key != NULL)
	{
		*key = ft_strndup(*str, *end_key - *str);
		*value = ft_strdup(*end_key + 1);
		if (*value == NULL)
			fatal_error("ft_strndup");
	}
	else
	{
		*key = ft_strdup(*str);
		if (*key == NULL)
			fatal_error("ft_strndup");
		*value = NULL;
	}
}

int	set_env_list(t_env **env, char *str)
{
	char	*key;
	char	*value;
	char	*end_key;

	if (str == NULL)
		return (-1);
	else
		set_env_list_if(&end_key, &key, &str, &value);
	if (is_key_in_env(key, *env))
		update_value_to_env(env, key, value);
	else
	{
		if (!is_variable(key))
			return (free_key_and_value(key, value));
		add_key_value_to_env(env, key, value);
	}
	free(key);
	free(value);
	return (0);
}
