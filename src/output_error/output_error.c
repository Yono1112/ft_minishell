/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:09:29 by yumaohno          #+#    #+#             */
/*   Updated: 2023/04/01 17:28:44 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_error = false;

void	fatal_error(const char *str)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", str);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *str)
{
	dprintf(STDERR_FILENO, "Assert Error: %s\n", str);
	exit(255);
}

void	todo(const char *msg)
{
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	exit(status);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	syntax_error = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *token)
{
	syntax_error = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	while (token && token->kind != TK_EOF)
		token = token->next;
	*rest = token;
}
