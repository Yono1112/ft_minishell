/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_to_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:45 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 16:24:48 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	token_lstsize(t_token *token)
{
	size_t	count;

	count = 0;
	while (token && token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
			count++;
		token = token->next;
	}
	return (count);
}

char	**add_token_to_argv(t_token *token)
{
	size_t	len;
	char	**argv;
	size_t	i;

	len = token_lstsize(token);
	argv = ft_calloc(len + 1, sizeof(char *));
	if (argv == NULL)
		fatal_error("ft_calloc");
	i = 0;
	while (token != NULL && token->kind != TK_EOF)
	{
		if (token->word != NULL && token->kind == TK_WORD)
		{
			argv[i] = ft_strdup(token->word);
			if (argv[i] == NULL)
				fatal_error("ft_strdup");
			i++;
		}
		token = token->next;
	}
	return (argv);
}
