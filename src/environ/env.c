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

t_env	*add_key_value_to_env(t_env *env, char *key, char *value)
{
	// t_env	*current;

	// current = *env;
	// print_env(*env);
	// exit(0);
	// printf("key:%s, value:%s\n", key, value);
	// printf("current->key:%s, current->value:%s\n", current->key, current->value);
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
		// env = append_key_value_to_env(strdup(key), NULL);
		// if (env->key == NULL)
		// 	fatal_error("strdup");
		return (create_new_env_list(strdup(key), NULL));
	}
	else
	{
		// env = append_key_value_to_env(strdup(key), strdup(value));
		// if (env->key == NULL || env->value == NULL)
		// 	fatal_error("strdup");
		return (create_new_env_list(strdup(key), strdup(value)));
	}
	return (env);
}

t_env	*search_key(t_env **env, char *key)
{
	t_env	*current;
	printf("start search_key\n");
	current = *env;
	// printf("current->key:%s, current->value:%s\n", current->key, current->value);
	if (current->key == NULL || current == NULL)
		return (NULL);
	else
	{
		while (current)
		{
			if (strcmp(current->key, key) == 0)
				break ;
			current = current->next;
		}
	}
	return (current);
}

void	add_back_env_list(t_env **env, t_env *new_env)
{
	t_env	*tmp_env;

	printf("start add_back_env_list\n");
	printf("env->key:%s, env->value:%s\n", (*env)->key, (*env)->value);
	if (env == NULL || new_env == NULL)
		return ;
	if (*env == NULL)
	{
		printf("env is NULL\n");
		*env = new_env;
	}
	else
	{
		printf("env is not NULL\n");
		tmp_env = *env;
		while (tmp_env->next != NULL)
			tmp_env = tmp_env->next;
		tmp_env->next = new_env;
		printf("tmp_env->key:%s, tmp_env->value:%s\n", tmp_env->next->key, tmp_env->next->value);
	}
}

bool	is_fisrt_env_list(t_env **env)
{
	if ((*env) != NULL && (*env)->key == NULL && (*env)->value == NULL)
		return (true);
	else
		return (false);
}

void	add_key_value_to_env_double(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_env;
	t_env	*tmp_env;

	printf("start add_key_value_to_env_double\n");
	printf("key:%s, value:%s\n", key, value);
	if (key == NULL || !is_variable(key))
	{
		printf("key in NULL or key is not valid valiable name\n");
		return ;
	}
	current = *env;
	current = search_key(env, key);
	// search_key(env, key);
	// printf("current->key:%s, current->value:%s\n", current->key, current->value);
	if (current != NULL)
	{
		printf("current is not NULL\n");
		free(current->value);
		if (value == NULL)
			current->value = NULL;
		else
		{
			current->value = strdup(value);
			if (current->value == NULL)
				fatal_error("map_set strdup");
		}
	}
	else
	{
		printf("current is NULL\n");
		if (is_fisrt_env_list(env))
		{
			printf("true fiset_env_lise\n");
			(*env)->key = key;
			(*env)->value = value;
		}
		else
		{
			printf("false fiset_env_lise\n");
			if (value == NULL)
			{
				printf("value is NULL\n");
				new_env = create_new_env_list(strdup(key), NULL);
				if (new_env->key == NULL)
					fatal_error("strdup");
			}
			else
			{
				printf("value is not NULL\n");
				new_env = create_new_env_list(strdup(key), strdup(value));
				if (new_env->key == NULL || new_env->value == NULL)
					fatal_error("strdup");
				printf("new_env->key:%s, new_env->value:%s\n", new_env->key, new_env->value);
			}
			// add_back_env_list(env, new_env);
			if (*env == NULL)
				*env = new_env;
			else
			{
				tmp_env = *env;
				while (tmp_env->next != NULL)
					tmp_env = tmp_env->next;
				tmp_env->next = new_env;
			}
			// printf("tmp_env->key:%s, tmp_env->value:%s\n", tmp_env->next->key, tmp_env->next->value);
		}
		// printf("env->key:%s, env->value:%s\n", (*env)->key, (*env)->value);
	}
}

t_env	*set_env_list(t_env *env, char *str)
{
	char	*key;
	char	*value;
	char	*end_key;

	// printf("envp:%s\n", str);
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
	// print_env(env);
	// printf("env->key:%s, env->value:%s\n", env->key, env->value);
	free(key);
	free(value);
	return (env);
}

t_env	*init_env_list(char **envp)
{
	t_env	*env;
	t_env	*current;
	size_t	i;

	printf("start create_env_list\n");
	// print_envp(envp);
	i = 0;
	env = create_new_env_list(NULL, NULL);
	current = env;
	while (envp[i] != NULL)
	{
		// printf("envp[%zu]: %s\n", i, envp[i]);
		current->next = set_env_list(current, envp[i]);
		if (current->next == NULL)
			return (NULL);
		current = current->next;
		printf("env->key:%s, env->value:%s\n", current->key, current->value);
		i++;
	}
	return (env->next);
}
