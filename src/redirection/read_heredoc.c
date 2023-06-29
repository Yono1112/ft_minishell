/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:14:53 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/29 11:50:26 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	while_read_heredoc(const char *delimiter,
				bool is_delimiter_quote, t_env **env, int *pfd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_data.heredoc_sig_received || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (is_delimiter_quote)
			line = expand_heredoc_line(line, env);
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], NEW_LINE, ft_strlen(NEW_LINE));
		free(line);
	}
}

int	read_heredoc(const char *delimiter, bool is_delimiter_quote, t_env **env)
{
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while_read_heredoc(delimiter, is_delimiter_quote, env, pfd);
	if (g_data.heredoc_sig_received)
	{
		close(pfd[0]);
		return (-1);
	}
	close(pfd[1]);
	return (pfd[0]);
}
