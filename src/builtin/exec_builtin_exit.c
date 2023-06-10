/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:44:33 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/07 19:41:21 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_num(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\0')
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	exec_builtin_exit(char **argv)
{
	int	argc;	

	argc = count_argc(argv);
	if (argc == 1)
		exit(last_status);
	else if (argc == 2)
	{
		if (is_num(argv[1]))
			exit(atoi(argv[1]));
		else
		{
			xperror("exit: numeric argument required");
			exit(255);
		}
	}
	else if (argc > 2)
		xperror("exit: too many arguments");
	return (1);
}
