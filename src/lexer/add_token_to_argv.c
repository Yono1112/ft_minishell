/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_to_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:45 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/24 22:41:46 by rnaka            ###   ########.fr       */
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

	// printf("start add_token_to_argv\n");
	len = token_lstsize(token);
	argv = ft_calloc(len + 1, sizeof(char *));
	if (argv == NULL)
		fatal_error("ft_calloc");
	i = 0;
	while (token != NULL && token->kind != TK_EOF)
	{
		// printf("token->kind: %d\n", token->kind);
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

// static char	**tail_recursive(t_token *tok, int nargs, char **argv)
// {
// 	if (tok == NULL || tok->kind == TK_EOF)
// 		return (argv);
// 	argv = realloc(argv, (nargs + 2) * sizeof(char *));
// 	argv[nargs] = ft_strdup(tok->word);
// 	if (argv[nargs] == NULL)
// 		fatal_error("ft_strdup");
// 	argv[nargs + 1] = NULL;
// 	return (tail_recursive(tok->next, nargs + 1, argv));
// }
// 
// char	**add_token_to_argv(t_token *tok)
// {
// 	char	**argv;
// 
// 	argv = ft_calloc(1, sizeof(char *));
// 	if (argv == NULL)
// 		fatal_error("ft_calloc");
// 	return (tail_recursive(tok, 0, argv));
// }
