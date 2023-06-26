/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:33:23 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/26 19:05:37 by rnaka            ###   ########.fr       */
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

bool	check_is_filename(const char *path, const char *filename)
{
	struct stat	sb;

	if (path == NULL)
		return (false);
	else if (!ft_strcmp(filename, ""))
		return (false);
	else if (!ft_strcmp(filename, ".."))
		return (false);
	else if (access(path, F_OK) < 0)
		return (false);
	if (access(path, X_OK) < 0)
		err_exit(path, PER_DENY, 126);
	if (stat(path, &sb) < 0)
		fatal_error("fstat");
	if (!S_ISREG(sb.st_mode) && S_ISDIR(sb.st_mode))
		err_exit(filename, IS_DIR, 126);
	return (true);
}

static int	make_pathlen(char **end,
							char *path, char **value)
{
	size_t	path_len;

	*end = ft_strchr(*value, ':');
	if (*end)
		path_len = (size_t)(*end - *value);
	else
		path_len = ft_strlen(*value);
	if (path_len >= PATH_MAX)
		return (1);
	ft_memcpy(path, *value, path_len);
	path[path_len] = '\0';
	ft_strncat(path, "/", PATH_MAX - ft_strlen(path) - 1);
	return (0);
}

char	*check_cmd_path(const char *filename, t_env **env)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = ft_getenv("PATH", env);
	if (!value)
		return (NULL);
	while (*value)
	{
		if (make_pathlen(&end, path, &value))
			return (NULL);
		ft_strncat(path, filename, PATH_MAX - ft_strlen(path) - 1);
		if (access(path, X_OK) == 0)
		{
			dup = ft_strdup(path);
			if (!dup)
				return (NULL);
			return (dup);
		}
		if (end == NULL)
			break ;
		value = end + 1;
	}
	return (NULL);
}

int	wait_pipeline(pid_t last_child_pid)
{
	pid_t	wait_pid;
	int		status;
	int		wstatus;

	while (1)
	{
		g_data.sig = 0;
		wait_pid = wait(&wstatus);
		if (wait_pid == last_child_pid)
		{
			if (WIFSIGNALED(wstatus))
			{
				if (isatty(STDIN_FILENO))
					printf("\n");
			 	status = 128 + WTERMSIG(wstatus);
			}
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_pid < 0)
		{
			if (errno == ECHILD)
					break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

size_t	env_len(t_env *env)
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

char	**change_env_to_environ(t_env *env)
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

int	exec_cmd(t_node *node, t_env **env)
{
	pid_t		pid;
	int			status;

	while (node != NULL)
	{
		prepare_pipe(node);
		pid = fork();
		if (pid < 0)
			fatal_error("fork");
		else if (pid == CHILD_PID)
		{
			reset_signal_to_default();
			prepare_pipe_child(node);
			if (is_builtin(node))
			{
				status = exec_builtin_cmd(node, env);
				exit(status);
			}
			else
				exec_simple_cmd(node, env);
		}
		prepare_pipe_parent(node);
		node = node->next;
	}
	status = wait_pipeline(pid);
	return (status);
}

int	exec(t_node *node, t_env **env)
{
	int		status;

	status = 0;
	if (open_redirect_file(node, env) < 0)
		return (ERROR_OPEN_REDIR);
	if (node->next == NULL && is_builtin(node))
		status = exec_builtin_cmd(node, env);
	else
		status = exec_cmd(node, env);
	return (status);
}
