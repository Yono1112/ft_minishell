/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:33:23 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/22 14:56:01 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len = strlen(s1) + strlen(s2) + strlen(s3);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	k = 0;
	while (s3[k])
	{
		str[i + j + k] = s3[k];
		k++;
	}
	str[i + j + k] = '\0';
	return (str);
}

bool	check_is_filename(const char *path)
{
	if (path == NULL)
		return (false);
	if (access(path, F_OK) < 0)
		return (false);
	return (true);
}

char	*check_cmd_path(const char *filename, t_env **env)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;
	size_t	path_len;

	value = ft_getenv("PATH", env);
	if (!value)
	{
		fprintf(stderr, "Error: PATH environment variable is not set\n");
		return (NULL);
	}
	while (*value)
	{
		end = strchr(value, ':');
		if (end)
			path_len = (size_t)end - (size_t)value;
		else
			path_len = strlen(value);
		if (path_len >= PATH_MAX)
		{
			fprintf(stderr, "Error: PATH element is too long\n");
			return (NULL);
		}
		memcpy(path, value, path_len);
		path[path_len] = '\0';
		strncat(path, "/", PATH_MAX - strlen(path) - 1);
		strncat(path, filename, PATH_MAX - strlen(path) - 1);
		if (access(path, X_OK) == 0)
		{
			dup = strdup(path);
			if (!dup)
			{
				fprintf(stderr, "Error: %s\n", strerror(errno));
				return (NULL);
			}
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
		sig = 0;
		wait_pid = wait(&wstatus);
		// printf("wait_pid: %d", wait_pid);
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
	// printf("finish wait_pipeline\n");
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
	environ = calloc(len + 1, sizeof(char *));
	if (environ == NULL)
		fatal_error("calloc");
	i = 0;
	while (env)
	{
		if (env->value != NULL)
		{
			printf("env->key:%s\n", env->key);
			environ[i] = ft_strjoin_three(env->key, "=", env->value);
			i++;
		}
		env = env->next;
	}
	environ[i] = NULL;
	return (environ);
}

// static void	print_argv(char **argv)
// {
// 	size_t	i;
// 
// 	i = 0;
// 	while (argv[i])
// 	{
// 		printf("argv[%ld]:%s\n", i, argv[i]);
// 		i++;
// 	}
// }

void	exec_simple_cmd(t_node *node, t_env **env)
{
	char		**environ;
	char		*path;
	char		**argv;

	// printf("start exec_simple_cmd\n");
	argv = NULL;
	if (node->command->redirects != NULL)
		do_redirect(node->command->redirects);
	if (node->command->args != NULL)
		argv = add_token_to_argv(node->command->args);
	else if (node->command->args == NULL && node->command->redirects != NULL)
		exit (0);
	// print_argv(argv);
	path = argv[0];
	// printf("path:%s\n", path);
	if (strchr(path, '/') == NULL)
		path = check_cmd_path(path, env);
	if (!check_is_filename(path))
		err_exit(argv[0], "command not found", 127);
	environ = change_env_to_environ(*env);
	// printf("==============================\n");
	// print_envp(environ);
	// printf("==============================\n");
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
		// printf("start exec_cmd\n");
		prepare_pipe(node);
		pid = fork();
		// printf("fork=============================================\n");
		if (pid < 0)
			fatal_error("fork");
		else if (pid == CHILD_PID)
		{
			// printf("start child_process\n");
			reset_signal_to_default();
			prepare_pipe_child(node);
			if (is_builtin(node))
			{
				// printf("exec_builtin_cmd\n");
				status = exec_builtin_cmd(node, env);
				exit(status);
			}
			else
			{
				// printf("exec_simple_cmd\n");
				exec_simple_cmd(node, env);
			}
		}
		// printf("start parent_process\n");
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
	{
		// printf("exec_builtin_cmd in parent process\n");
		status = exec_builtin_cmd(node, env);
	}
	else
	{
		status = exec_cmd(node, env);
		// printf("finish exec_cmd\n");
	}
	return (status);
}

// int	exec(t_node *node)
// {
// 	int		status;
// 	pid_t	last_child_pid;
// 
// 	if (open_redirect_file(node) < 0)
// 		return (ERROR_OPEN_REDIR);
// 	// printf("finish open_redirect\n");
// 	last_child_pid = exec_cmd(node);
// 	// printf("finish exec_cmd\n");
// 	status = wait_pipeline(last_child_pid);
// 	return (status);
// }
