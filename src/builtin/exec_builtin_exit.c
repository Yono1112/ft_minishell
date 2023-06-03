/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:44:33 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/02 10:30:17 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_numeric(char *s)
{
	if (!isdigit(*s))
		return (false);
	while (*s)
	{
		if (!isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int	exec_builtin_exit(char **argv)
{
	long	res;
	char	*arg;
	char	*endptr;

	if (argv[1] == NULL)
		exit(last_status);
	if (argv[2])
	{
		xperror("exit: too many arguments");
		return (1);
	}
	arg = argv[1];
	if (is_numeric(arg))
	{
		errno = 0;
		res = strtol(arg, &endptr, 10);
		if (errno == 0 && *endptr == '\0')
			exit((int)res);
	}
	xperror("exit: numeric argument required");
	exit(255);
}
