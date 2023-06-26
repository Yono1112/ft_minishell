/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:44:33 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 04:48:31 by yuohno           ###   ########.fr       */
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

static int	exec_builtin_exit_is_num(char **argv, int argc)
{
	if (argc == 2)
		return (0);
	else
	{
		builtin_error("exit", argv[1], "exit: too many arguments");
		return (1);
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
		{
			if (exec_builtin_exit_is_num(argv, argc))
				return (1);
			else
				exit(atol(argv[1]));
		}
		else
		{
			builtin_error("exit", argv[1], "exit: too many arguments");
			exit(255);
		}
	}
	return (1);
}
