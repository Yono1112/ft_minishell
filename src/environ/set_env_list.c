/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:08:43 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/23 00:45:30 by rnaka            ###   ########.fr       */
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
		if (strcmp(update_env->key, key) == 0)
			break ;
		update_env = update_env->next;
	}
	free(update_env->value);
	update_env->value = strdup(value);
	if (update_env->value == NULL)
		fatal_error("strdup");
}

void	add_key_value_to_env(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*last_env;

	// printf("start add_key_value_to_env\n");
	// printf("key:%s, value:%s\n", key, value);
	if (value == NULL)
	{
		new_env = create_new_env_list(strdup(key), NULL);
		if (new_env->key == NULL)
			fatal_error("strdup");
	}
	else
	{
		new_env = create_new_env_list(strdup(key), strdup(value));
		if (new_env->key == NULL || new_env->value == NULL)
			fatal_error("strdup");
	}
	// printf("new_env->key:%s, new_env->value:%s\n", new_env->key, new_env->value);
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
		if (strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

int	set_env_list(t_env **env, char *str)
{
	char	*key;
	char	*value;
	char	*end_key;

	// printf("envp:%s\n", str);
	if (str == NULL)
		return (-1);
	else
	{
		end_key = strchr(str, '=');
		// printf("end_key:%s\n", end_key);
		if (end_key != NULL)
		{
			// printf("end_key is not NULL\n");
			key = strndup(str, end_key - str);
			value = strdup(end_key + 1);
			if (value == NULL)
				fatal_error("strndup");
		}
		else
		{
			// printf("end_key is NULL\n");
			key = strdup(str);
			if (key == NULL)
				fatal_error("strndup");
			value = NULL;
		}
		// printf("%ld\n", end_key - str);
	}
	// printf("key:%s, value:%s\n", key, value);
	if (is_key_in_env(key, *env))
	{
		// printf("true is_key_in_env\n");
		update_value_to_env(env, key, value);
	}
	else
	{
		// printf("false is_key_in_env\n");
		if (!is_variable(key))
		{
			free(key);
			free(value);
			return (-1);
		}
		add_key_value_to_env(env, key, value);
		// printf("env->key:%s, env->value:%s\n", (*env)->key, (*env)->value);
	}
	free(key);
	free(value);
	return (0);
}
