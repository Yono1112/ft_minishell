/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:05:12 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 17:58:41 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_node *node)
{
	t_node	*next_node;

	while (node != NULL)
	{
		if (node->command->redirects)
		{
			free_token(node->command->redirects->filename);
			free_token(node->command->redirects->delimiter);
			free(node->command->redirects);
		}
		if (node->command)
		{
			free_token(node->command->args);
			free(node->command);
		}
		next_node = node->next;
		free(node);
		node = next_node;
	}
}

void	free_token(t_token *token)
{
	t_token	*next_token;

	while (token != NULL)
	{
		if (token->word)
			free(token->word);
		next_token = token->next;
		free(token);
		token = next_token;
	}
}

void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
