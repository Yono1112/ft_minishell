/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:40:13 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/13 20:58:18 by yuohno           ###   ########.fr       */
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

static t_env	*create_new_env_list()
{
	t_env	*env;

	env = calloc(1, sizeof(*env));
	if (env == NULL)
		fatal_error("calloc");
	env->key = NULL;
	env->value = NULL;
	return (env);
}

static t_env	*append_key_value_to_env(char *key, char *value)
{
	t_env	*env;

	env = calloc(1, sizeof(*env));
	if (env == NULL)
		fatal_error("calloc");
	env->key = key;
	env->value = value;
	return (env);
}

static t_env	*add_key_value_to_env(t_env *env, char *key, char *value)
{
	printf("key:%s, value:%s\n", key, value);
	if (!is_variable(key) || key == NULL)
		return (NULL);
	if (env->key != NULL)
	{
		while (env)
		{
			if (strcmp(env->key, key) == 0)
			{
				printf("break\n");
				break;
			}
			env = env->next;
		}
	}
	if (env != NULL)
	{
		if (value == NULL)
			env = NULL;
		else
		{
			free(env->value);
			env->value = strdup(value);
			if (env->value == NULL)
				fatal_error("strdup");
		}
	}
	if (value == NULL)
	{
		env = append_key_value_to_env(strdup(key), NULL);
		if (env->key == NULL)
			fatal_error("strdup");
	}
	else
	{
		env = append_key_value_to_env(strdup(key), strdup(value));
		if (env->key == NULL || env->value == NULL)
			fatal_error("strdup");
	}
	return (env);
}

static t_env	*set_env_list(t_env *env, char *str)
{
	char	*key;
	char	*value;
	char	*end_key;
	int		ret;

	// printf("envp:%s\n", str);
	ret = 0;
	if (str == NULL)
		return (NULL);
	end_key = strchr(str, '=');
	// printf("end_key:%s\n", end_key);
	key = strndup(str, end_key - str);
	if (key == NULL)
		fatal_error("strndup");
	value = strdup(end_key + 1);
	if (value == NULL)
		fatal_error("strndup");
	// printf("key:%s, value:%s\n", key, value);
	// printf("===============================================\n");
	// printf("env->key:%s, env->value:%s\n", env->key, env->value);
	env = add_key_value_to_env(env, key, value);
	printf("env->key:%s, env->value:%s\n", env->key, env->value);
	return (env);
}

t_env	*init_env_list(char **envp)
{
	t_env	*env;
	size_t	i;

	// printf("start create_env_list\n");
	// print_envp(envp);
	i = 0;
	env = create_new_env_list();
	// printf("env->key:%s, env->value:%s\n", env->key, env->value);
	// env->key = "key";
	// env->value = "value";
	while (envp[i] != NULL)
	{
		// printf("envp[%zu]: %s\n", i, envp[i]);
		env = set_env_list(env, envp[i]);
		if (env == NULL)
			return (NULL);
		i++;
	}
	return (env);
}
