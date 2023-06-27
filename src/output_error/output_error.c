/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:09:29 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/27 21:23:38 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *str)
{
	write(STDERR_FILENO, FATAL_ERROR, ft_strlen(FATAL_ERROR));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	exit(EXIT_FAILURE);
}

void	err_exit(const char *location, const char *msg, int status)
{
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	exit(status);
}

void	tokenize_error(const char *location, char **rest,
			char *line, int *syntax_error)
{
	*syntax_error = 1;
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, SYNTAX_ERROR, ft_strlen(SYNTAX_ERROR));
	write(STDERR_FILENO, ERROR_LEXER_MSG, ft_strlen(ERROR_LEXER_MSG));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest,
			t_token *token, int *syntax_error)
{
	*syntax_error = 1;
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, SYNTAX_ERROR, ft_strlen(SYNTAX_ERROR));
	write(STDERR_FILENO, ERROR_PARSE_MSG, ft_strlen(ERROR_PARSE_MSG));
	write(STDERR_FILENO, "`", ft_strlen("`"));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, "'", ft_strlen("'"));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	while (token && token->kind != TK_EOF)
		token = token->next;
	*rest = token;
}

void	builtin_error(char *func, char *name, char *err_message)
{
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, func, ft_strlen(func));
	write(STDERR_FILENO, ": ", 2);
	if (name)
	{
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, ": ", 2);
	}
	if (err_message)
		write(STDERR_FILENO, err_message, ft_strlen(err_message));
	write(STDERR_FILENO, NEW_LINE, 1);
}
