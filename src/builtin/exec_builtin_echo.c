
#include "minishell.h"

int	count_argc(char **argv)
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
	if (second_arg[i] == '\0')
		return (false);
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
		write(STDOUT_FILENO, &str[i], 1);
		// if (str[i + 1] == '\0')
		// {
		// 	write(1, "=", 1);
		// 	// write(1, " ", 1);
		// 	break ;
		// }
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
	// printf("argc:%d\n", argc);
	if (argc == 1)
		write(STDOUT_FILENO, "\n", 1);
	else
	{
		if ('-' == argv[1][0] && check_valid_option(argv[1]))
			is_option = 1;
		i = is_option + 1;
		while (i < argc)
		{
			// write(STDOUT_FILENO, argv[i], strlen(argv[i]));
			write_str(argv[i]);
			if (i + 1 < argc && ((ft_strlen(argv[i]) > 0  && ft_strlen(argv[i + 1]) >= 0 )|| ((ft_strlen(argv[1]) >= 0 && ft_strlen(argv[i + 1]) > 0))|| (ft_strlen(argv[i]) == 0 && ft_strlen(argv[i + 1]) == 0)))
			{
			 	// printf("argc\n");
			  	write(1, " ", 1);
			}
			i++;
		}
		if (!is_option)
			write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
