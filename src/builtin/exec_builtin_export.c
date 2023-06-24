/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:00:07 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/22 14:59:43 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_env(t_env *current, t_env *next)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = current->key;
	current->key = next->key;
	next->key = tmp_key;
	tmp_value = current->value;
	current->value = next->value;
	next->value = tmp_value;
}

static t_env	*bubble_sort_env(t_env *env)
{
	t_env	*current_env;
	t_env	*next_env;

	current_env = env;
	next_env = NULL;
	while (current_env != NULL)
	{
		next_env = current_env->next;
		while (next_env != NULL)
		{
			if (current_env->value != NULL && next_env->value != NULL && strcmp(current_env->key, next_env->key) > 0)
				swap_env(current_env, next_env);
			next_env = next_env->next;
		}
		current_env = current_env->next;
	}
	return (env);
}

static void	print_environ_variable(t_env **env)
{
	t_env	*sorted_env;

	// printf("start print_environ_variable\n");
	// if (env == NULL)
	// 	printf("env is NULL\n");
	// print_env(*env);
	sorted_env = bubble_sort_env(*env);
	// print_env(sorted_env);
	// printf("========================================\n");
	while (sorted_env != NULL)
	{
		if (sorted_env->value != NULL)
			printf("declare -x %s=\"%s\"\n", sorted_env->key, sorted_env->value);
		else
			printf("declare -x %s\n", sorted_env->key);
		sorted_env = sorted_env->next;
	}
	// printf("finish print_environ_variable\n");
}

int	exec_builtin_export(char **argv, t_env **env)
{
	int	argc;
	size_t	i;
	int	status;

	status = 0;
	argc = count_argc(argv);
	if (argc == 1)
		print_environ_variable(env);
	else
	{
		i = 1;
		while (argv[i])
		{
			if (set_env_list(env, argv[i]) == -1 ) 
			{
				builtin_error("export", argv[i], "not a valid identifier");
				status = 1;
			}
			i++;
		}
	}
	// print_env(*env);
	return (status);
}
