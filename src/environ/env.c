/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:40:13 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/21 16:32:14 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_envp(char **envp)
// {
// 	size_t	i;
// 
// 	i = 0;
// 	while (envp[i])
// 	{
// 		printf("envp[%zu]: %s\n", i, envp[i]);
// 		i++;
// 	}
// }

bool	is_variable(char *str)
{
	size_t	i;

	i = 0;
	if (!is_alpha_under(str[i]))
		return (false);
	i++;
	while (str[i])
	{
		if (!is_alpha_num_under(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static t_env	*create_new_env_list(char *key, char *value)
{
	t_env	*env;

	// env = calloc(1, sizeof(*env));
	env = calloc(1, sizeof(*env));
	if (env == NULL)
		fatal_error("calloc");
	env->key = key;
	env->value = value;
	return (env);
}

void	update_value_to_env(t_env **env, char *key, char *value)
{
	t_env	*update_env;

	update_env = *env;
	// if (update_env == NULL || update_env->key == NULL)
	// 	return ;
	while (update_env)
	{
		if (strcmp(update_env->key, key) == 0)
			break ;
		update_env = update_env->next;
	}
	// if (update_env == NULL)
	// 	return ;
	free(update_env->value);
	if (value == NULL)
		update_env->value = NULL;
	else
	{
		update_env->value = strdup(value);
		if (update_env->value == NULL)
			fatal_error("strdup");
	}
}

void	add_key_value_to_env(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*last_env;

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

int	set_env_list(t_env **env, char *str, bool is_export)
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
		if (end_key == NULL && is_export)
		{
			printf("value is NULL && true is_export\n");
			return (-1);
		}
		key = strndup(str, end_key - str);
		if (key == NULL)
			fatal_error("strndup");
		value = strdup(end_key + 1);
		if (value == NULL)
			fatal_error("strndup");
	}
	printf("key:%s, value:%s\n", key, value);
	if (is_key_in_env(key, *env))
	{
		printf("true is_key_in_env\n");
		update_value_to_env(env, key, value);
	}
	else
	{
		printf("false is_key_in_env\n");
		add_key_value_to_env(env, key, value);
	}
	free(key);
	free(value);
	return (0);
}

t_env	*init_env_list(char **envp)
{
	t_env	*env;
	size_t	i;

	printf("start create_env_list\n");
	// print_envp(envp);
	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		printf("===============================\n");
	 	printf("envp[%zu]: %s\n", i, envp[i]);
		set_env_list(&env, envp[i], false);
		printf("env->key:%s, env->value:%s\n", env->key, env->value);
		i++;
	}
	return (env);
}
