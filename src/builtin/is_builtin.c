/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:28:23 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/22 22:50:09 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_node *node)
{
	char *const	builtin_commands[] = {"exit", "echo","cd","pwd"};
	size_t		i;
	size_t		builtin_len;
	char		*builtin_command;

	// printf("start is_builtin\n");
	if (node != NULL && node->command != NULL && node->command->args != NULL && node->command->args->word != NULL)
	{
		builtin_command = node->command->args->word;
		// printf("builtin_command: %s\n", builtin_command);
		builtin_len = sizeof(builtin_commands) / sizeof(*builtin_commands);
		i = 0;
		while (i < builtin_len)
		{
			if (!strcmp(builtin_command, builtin_commands[i]))
			{
				// printf("true is_builtin\n");
				return (true);
			}
			i++;
		}
	}
	// printf("false is_builtin\n");
	return (false);
}
