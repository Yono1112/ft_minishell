/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:56:06 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 04:57:21 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_control_operator(t_token *token)
{
	static char *const	operators[] = {"|", "\n"};
	size_t				i;
	size_t				operators_len;

	i = 0;
	operators_len = sizeof(operators) / sizeof(*operators);
	while (i < operators_len)
	{
		if (!ft_strncmp(token->word, operators[i], ft_strlen(operators[i])))
			return (true);
		i++;
	}
	return (false);
}

static void	simple_command_conditions(t_token **token,
				int *syntax_error, t_node **command)
{
	if ((*token)->kind == TK_WORD)
	{
		add_token_to_node(&(*command)->args, tokendup((*token)));
		(*token) = (*token)->next;
	}
	else if (check_operator((*token), ">") && (*token)->next->kind == TK_WORD)
		add_operator_to_node(&(*command)->redirects,
			create_new_redirect_out(&(*token), (*token)));
	else if (check_operator((*token), "<") && (*token)->next->kind == TK_WORD)
		add_operator_to_node(&(*command)->redirects,
			create_new_redirect_in(&(*token), (*token)));
	else if (check_operator((*token), ">>") && (*token)->next->kind == TK_WORD)
		add_operator_to_node(&(*command)->redirects,
			create_new_redirect_append(&(*token), (*token)));
	else if (check_operator((*token), "<<") && (*token)->next->kind == TK_WORD)
		add_operator_to_node(&(*command)->redirects,
			create_new_redirect_heredoc(&(*token), (*token)));
	else
		parse_error(ERROR_PARSE_LOCATION, &(*token), (*token), syntax_error);
}

t_node	*simple_command(t_token **rest, t_token *token, int *syntax_error)
{
	t_node	*command;

	command = create_new_node_list(ND_SIMPLE_CMD);
	while (token && token->kind != TK_EOF && !is_control_operator(token))
		simple_command_conditions(&token, syntax_error, &command);
	*rest = token;
	return (command);
}
