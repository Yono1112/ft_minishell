/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:09:29 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/25 19:14:00 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	syntax_error = false;

// static void	perror_prefix(void)
// {
// 	dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
// 	// write(STDERR_FILENO, "")
// }

void	fatal_error(const char *str)
{
	// dprintf(STDERR_FILENO, "Fatal Error: %s\n", str);
	write(STDERR_FILENO, FATAL_ERROR, ft_strlen(FATAL_ERROR));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	exit(EXIT_FAILURE);
}

void	assert_error(const char *str)
{
	// dprintf(STDERR_FILENO, "Assert Error: %s\n", str);
	write(STDERR_FILENO, ASSERT_ERROR, ft_strlen(ASSERT_ERROR));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	exit(255);
}

void	todo(const char *msg)
{
	// dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	write(STDERR_FILENO, TODO_ERROR, ft_strlen(TODO_ERROR));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	// dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	exit(status);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	syntax_error = true;
	// dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, SYNTAX_ERROR, ft_strlen(SYNTAX_ERROR));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *token)
{
	syntax_error = true;
	// dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, SYNTAX_ERROR, ft_strlen(SYNTAX_ERROR));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, NEW_LINE, ft_strlen(NEW_LINE));
	while (token && token->kind != TK_EOF)
		token = token->next;
	*rest = token;
}

void	xperror(const char *location)
{
	// perror_prefix();
	// dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	perror(location);
}

void	builtin_error(char *func, char *name, char *err_message, char *perror_message)
{
	// perror_prefix();
	// dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
	write(STDERR_FILENO, ERROR_PREFIX, ft_strlen(ERROR_PREFIX));
	write(STDERR_FILENO, func, ft_strlen(func));
	write(STDERR_FILENO, ": ", 2);
	// dprintf(STDERR_FILENO, "%s: ", func);
	if (name)
	{
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, ": ", 2);
		// dprintf(STDERR_FILENO, "%s: ", name);
	}
	if (err_message)
		write(STDERR_FILENO, err_message, ft_strlen(err_message));
	if (perror_message)
		perror(perror_message);
	write(STDERR_FILENO, NEW_LINE, 1);
}
