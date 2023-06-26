/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:42:08 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 00:43:31 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	while (*s3)
		*str++ = *s3++;
	*str = '\0';
	return (str);
}

static size_t	env_len(t_env *env)
{
	size_t	len;

	len = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
			len++;
		env = env->next;
	}
	return (len);
}

static char	**change_env_to_environ(t_env *env)
{
	char	**environ;
	size_t	len;
	size_t	i;

	len = env_len(env);
	environ = ft_calloc(len + 1, sizeof(char *));
	if (environ == NULL)
		fatal_error("ft_calloc");
	i = 0;
	while (env)
	{
		if (env->value != NULL)
		{
			environ[i] = ft_strjoin_three(env->key, "=", env->value);
			i++;
		}
		env = env->next;
	}
	environ[i] = NULL;
	return (environ);
}

void	exec_simple_cmd(t_node *node, t_env **env)
{
	char		**environ;
	char		*path;
	char		**argv;

	argv = NULL;
	if (node->command->redirects != NULL)
		do_redirect(node->command->redirects);
	if (node->command->args != NULL)
		argv = add_token_to_argv(node->command->args);
	else if (node->command->args == NULL && node->command->redirects != NULL)
		exit (0);
	if (ft_strchr(argv[0], '/') == NULL)
		path = check_cmd_path(argv[0], env);
	else
		path = argv[0];
	if (!check_is_filename(path, argv[0]))
		err_exit(argv[0], COMMAND_NOT_FOUND, 127);
	environ = change_env_to_environ(*env);
	execve(path, argv, environ);
	free_argv(argv);
	fatal_error("execve");
}
