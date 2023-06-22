#include<unistd.h>
#include<limits.h>
#include"minishell.h"

int	count_arg(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

int	cd_argv(char **argv, t_path *path)
{
	int	status;

	status = chdir(argv[1]);
	if (status)
	// ---------------------------------------------------
	{
		// error;
		return (1);
	}
	//----------------------------------------------------
	free(path->old);
	path->old = path->pwd;
	path->pwd = strdup(argv[1]);
	return (status);
}

int	cd_home(t_path *path)
{
	int	status;
	char	*arg;

	arg = getenv("HOME");//<-ここ書き換え！！！！！！！！！！！！！！！！！！！！！
	if (!arg)
		return (1);
	status = chdir(arg);
	if (status)
	// ---------------------------------------------------
	{
		// error;
		return (1);
	}
	//----------------------------------------------------
	free(path->old);
	path->old = path->pwd;
	path->pwd = strdup(arg);//<-ここ書き換え！！！！！！！！！！！！！！
	return (status);
}

int	cd_prev(t_path *path)
{
	int	status;
	char	*save;

	status = 0;
	if (!path->old)
		return (1);
	status = chdir(path->old);
	if (!status)
		return (status);
	save = path->old;
	path->old = path->pwd;
	path->pwd = save;
	return (status);
}

int	exec_builtin_cd(char **argv, t_path *path)
{
	int argc;

	argc = count_arg(argv);
	if (argc == 2 && !strcmp(argv[1], "-"))
		return (cd_prev(path));
	else if(argc == 1)
		cd_home(path);
	return (cd_argv(argv, path));
}
