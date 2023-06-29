/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 04:47:57 by rnaka             #+#    #+#             */
/*   Updated: 2023/06/27 18:51:12 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
}

static int	is_option(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (!str[i] || str[i] != '-')
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			flag = 0;
		else
			return (1);
		i++;
	}
	return (flag);
}


int	exec_builtin_echo(char **argv)
{
	int	i;
	int	j;
	int	argc;

	i = 0;
	j = 1;
	argc = count_argc(argv);
	if (argc == 1)
		write(STDOUT_FILENO, "\n", 1);
	else
	{
		while (argv[j] && !is_option(argv[j]))
			j++;
		i = j;
		while (i < argc)
		{
			write_str(argv[i]);
			if (i + 1 < argc)
				write(1, " ", 1);
			i++;
		}
		if (j == 1)
			write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
