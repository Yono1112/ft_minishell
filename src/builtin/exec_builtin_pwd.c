#include "minishell.h"
#include <unistd.h>

int	exec_builtin_pwd(char **argv, t_env **env)
{
	char	*cwd;

	(void)argv;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		write(STDOUT_FILENO, cwd, strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		update_value_to_env(env, "PWD", cwd);
		return (0);
	}
	return (1);
}
