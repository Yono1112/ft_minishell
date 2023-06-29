/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:44:33 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/29 16:11:45 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_num(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\0')
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	exit_numeric(char **argv, int argc)
{
	int		is_over_long;
	long	result;

	is_over_long = 0;
	if (argc == 2)
	{
		result = ft_atol(argv[1], &is_over_long);
		if (!is_over_long)
			exit(result);
		else
		{
			builtin_error("exit", argv[1], "numric argument required");
			exit(255);
		}
	}
	builtin_error("exit", NULL, "too many arguments");
	return (1);
}

static void	exit_not_numeric(char *str, int argc)
{
	if (argc > 2)
	{
		builtin_error("exit", NULL, "numric argument required");
		exit(255);
	}
	else
	{
		builtin_error("exit", str, "numric argument required");
		exit(255);
	}
}

int	exec_builtin_exit(char **argv)
{
	int	argc;

	argc = count_argc(argv);
	if (argc == 1)
		exit(g_data.last_status);
	else
	{
		if (is_num(argv[1]))
			return (exit_numeric(argv, argc));
		else
			exit_not_numeric(argv[1], argc);
	}
	return (1);
}
