#include<unistd.h>
#include<limits.h>
#include"minishell.h"

typedef struct s_path
{
	char	*pwd;
	char	*old;
}	t_path;


int	cd_argv(char **argv, struct s_path *path)
{
	int	status;

	(void)argv;
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
	path->pwd = strdup(argv[1]);//NULLチェックは必要か？
	return (status);
}

int	cd_home()
{
	char	*home;
	
	home = getenv("HOME");
	if (!home)
		return (1);
	return (chdir(home));
}

int	cd_prev()
{
	char	*prev;
	char	currentdir[PATH_MAX];

	prev = getenv("OLDPWD");
	getcwd(currentdir, PATH_MAX);
	//printf("%s\n",currentdir);
	if (!prev)
		return (1);
	return (chdir(prev));
}

int	count_arg(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

int	exec_builtin_cd(char **argv)
{
	int i;
	int argc;

	// ----------------------------------------------------------------
	// minishell実行時に以下の値を取得しておく
	struct s_path path = {getenv("PWD"),getenv("OLDPWD")};
	// printf("%s\n", path.pwd);
	int j = 0;
	// \while (argv[j])
	// {j++;}
	printf("%d\n",j);
	return 0;
	// ----------------------------------------------------------------
	argc = count_arg(argv);
	(void)i;
	if (argc == 1)
		 return (cd_home());
	else if (!strcmp(argv[1], "-"))
		 return (cd_prev());
	return (cd_argv(argv, &path));
}
