#include "minishell.h"
#include <unistd.h>

int	exec_builtin_pwd(char **argv, t_env **env)
{
	char	*cwd;

	(void)argv;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		if (!ft_getenv("PWD", env))
			add_key_value_to_env(env, "PWD", cwd);
		else
			update_value_to_env(env, "PWD", cwd);
		free(cwd);
		return (0);
	}
	free(cwd);
	return (1);
}

int	get_cwd(t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		if (!ft_getenv("PWD", env))
			add_key_value_to_env(env, "PWD", cwd);
		else
			update_value_to_env(env, "PWD", cwd);
		free(cwd);
		return (0);
	}
	return (1);
}
