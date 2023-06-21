#include "minishell.h"
#include <unistd.h>

int	exec_builtin_pwd(char **argv)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = getenv("PWD");
	if (pwd)
	{
		write(STDOUT_FILENO, pwd, strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (getcwd(cwd,PATH_MAX) != NULL)
	{
		write(STDOUT_FILENO, cwd, strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	return (1);
}
