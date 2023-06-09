/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:28:23 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 02:27:06 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_node *node)
{
	char *const	builtin_commands[]
		= {"exit", "echo", "export", "unset", "env", "cd", "pwd"};
	size_t		i;
	size_t		builtin_len;
	char		*builtin_command;

	if (node != NULL && node->command != NULL
		&& node->command->args != NULL && node->command->args->word != NULL)
	{
		builtin_command = node->command->args->word;
		builtin_len = sizeof(builtin_commands) / sizeof(*builtin_commands);
		i = 0;
		while (i < builtin_len)
		{
			if (!ft_strcmp(builtin_command, builtin_commands[i]))
				return (true);
			i++;
		}
	}
	return (false);
}
