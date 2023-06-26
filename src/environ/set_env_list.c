/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:08:43 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 18:13:35 by rnaka            ###   ########.fr       */
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
