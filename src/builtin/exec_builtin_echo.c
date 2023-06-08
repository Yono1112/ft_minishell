#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"

static int	count_arg(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
		i++;
	return i;
}

static int	check_valid_option(char *second_arg)
{
	int i;

	i = 1;
	while (second_arg[i])
	{
		if (second_arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	write_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, str + i, 1);
		i++;
	}
}


int	exec_builtin_echo(char **argv)
{
	int i;
	int flag;
	int argc;

	i = 0;
	flag = 0;
	argc = count_arg(argv);
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	if ('-' == argv[1][0])
	{
		if (!check_valid_option(argv[1]))
			flag = 1;
	}
	i = flag + 1;
	while (i < argc)
	{
		write_str(argv[i]);
		if (i + 1 < argc)
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

//int main(int argc, char **argv)
//{
//	if (argc < 1)
//		return 1;
//	exec_builtin_echo(argv + 1);
//}

