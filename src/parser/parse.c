/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:17:59 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/17 18:22:49 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define STDOUT_FILENO 1
#define STDIN_FILENO 0

void	add_token_to_node(t_token **node_token, t_token *new_token)
{
	t_token	*tmp_token;

	if (*node_token == NULL)
		*node_token = new_token;
	else
	{
		tmp_token = *node_token;
		while (tmp_token->next != NULL)
			tmp_token = tmp_token->next;
		tmp_token->next = new_token;
	}
}

void	add_operator_to_node(t_node **node, t_node *new_node)
{
	t_node	*tmp_node;

	if (*node == NULL)
		*node = new_node;
	else
	{
		tmp_node = *node;
		while (tmp_node->next != NULL)
			tmp_node = tmp_node->next;
		tmp_node->next = new_node;
	}
}

t_token	*tokendup(t_token *token)
{
	char	*word;

	word = strdup(token->word);
	if (word == NULL)
		fatal_error("strdup");
	return (create_new_token_list(word, token->kind));
}

t_node	*create_new_node_list(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

bool	check_operator(t_token *token, char *op)
{
	return (token->kind == TK_OP && strcmp(token->word, op) == 0);
}

t_node	*create_new_redirect_out(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_OUT);
	node->filename = tokendup(token->next);
	node->targetfd = STDOUT_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*create_new_redirect_in(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_IN);
	node->filename = tokendup(token->next);
	node->targetfd = STDIN_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*create_new_redirect_append(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_APPEND);
	node->filename = tokendup(token->next);
	node->targetfd = STDOUT_FILENO;
	*rest = token->next->next;
	return (node);
}

t_node	*create_new_redirect_heredoc(t_token **rest, t_token *token)
{
	t_node	*node;

	node = create_new_node_list(ND_REDIR_HEREDOC);
	node->delimiter = tokendup(token->next);
	node->targetfd = STDIN_FILENO;
	*rest = token->next->next;
	return (node);
}

bool	is_control_operator(t_token *token)
{
	static char *const	operators[] = {"||", "|", "&", "&&", ";", ";;", "(", ")", "\n"};
	size_t				i;
	size_t				operators_len;

	i = 0;
	operators_len = sizeof(operators) / sizeof(*operators);
	while (i < operators_len)
	{
		if (!strncmp(token->word, operators[i], strlen(operators[i])))
			return (true);
		i++;
	}
	return (false);
}

t_node	*simple_command(t_token **rest, t_token *token)
{
	t_node	*command;

	command = create_new_node_list(ND_SIMPLE_CMD);
	while (token && token->kind != TK_EOF && !is_control_operator(token))
	{
		// printf("token_kind: %u\n", token->kind);
		if (token->kind == TK_WORD)
		{
			add_token_to_node(&command->args, tokendup(token));
			token = token->next;
		}
		else if (check_operator(token, ">") && token->next->kind == TK_WORD)
			add_operator_to_node(&command->redirects,
				create_new_redirect_out(&token, token));
		else if (check_operator(token, "<") && token->next->kind == TK_WORD)
			add_operator_to_node(&command->redirects,
				create_new_redirect_in(&token, token));
		else if (check_operator(token, ">>") && token->next->kind == TK_WORD)
			add_operator_to_node(&command->redirects,
				create_new_redirect_append(&token, token));
		else if (check_operator(token, "<<") && token->next->kind == TK_WORD)
			add_operator_to_node(&command->redirects,
				create_new_redirect_heredoc(&token, token));
		else
			todo("Implement parser");
	}
	*rest = token;
	return (command);
}

t_node	*pipeline(t_token **rest, t_token *token)
{
	t_node	*node;

	// printf("start pipeline\n");
	node = create_new_node_list(ND_PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&token, token);
	if (check_operator(token, "|"))
		node->next = pipeline(&token, token->next);
	*rest = token;
	// printf("finish pipeline\n");
	return (node);
}

t_node	*parse(t_token *token)
{
	return (pipeline(&token, token));
}
