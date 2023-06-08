
#include "minishell.h"

static int	count_argc(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
		i++;
	return (i);
}

static bool	check_valid_option(char *second_arg)
{
	int	i;

	i = 1;
	while (second_arg[i])
	{
		if (second_arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	write_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}


int	exec_builtin_echo(char **argv)
{
	int 	i;
	int 	is_option;
	int 	argc;

	i = 0;
	is_option = 0;
	argc = count_argc(argv);
	if (argc == 1)
		printf("\n");
	else
	{
		if ('-' == argv[1][0] && check_valid_option(argv[1]))
			is_option = 1;
		i = is_option + 1;
		while (i < argc)
		{
			write_str(argv[i]);
			if (i + 1 < argc)
				write(1, " ", 1);
			i++;
		}
		if (!is_option)
			printf("\n");
	}
	return (0);
}
