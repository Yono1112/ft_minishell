/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:16:31 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/29 03:35:15by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->word)
		free(token->word);
	free(token->next);
	free(token);
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

static bool	is_blank(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static void	skip_blank(char **skip_line, char *line)
{
	while (is_blank(*line))
		line++;
	*skip_line = line;
}

static bool	is_operator(char *line)
{
	static char *const	operators[] = {"||", "|", "&", "&&",
		";", ";;", "(", ")", "\n"};
	size_t				i;
	size_t				operators_len;

	i = 0;
	operators_len = sizeof(operators) / sizeof(*operators);
	while (i < operators_len)
	{
		if (!strncmp(line, operators[i], strlen(operators[i])))
			return (true);
		i++;
	}
	return (false);
}
static t_token	*add_operator_to_list(char **rest_line, char *line)
{
	static char *const	operators[] = {"||", "|", "&&", "&",
		";;", ";", "(", ")", "\n"};
	size_t				i;
	size_t				operators_len;
	char				*operator;
	char				*str;

	i = 0;
	operators_len = sizeof(operators) / sizeof(*operators);
	while (i < operators_len)
	{
		operator = operators[i];
		if (!strncmp(line, operators[i], strlen(operator)))
		{
			*rest_line = line + strlen(operator);
			str = strndup(line, strlen(operator));
			printf("operator: %s\n", str);
			if (!str)
				fatal_error("strndup");
			return (create_new_token_list(str, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
	return (NULL);
}

static bool	is_word(char *line)
{
	return (!is_blank(*line) && !is_operator(line));
}

static t_token	*add_word_to_list(char **rest_line, char *line)
{
	char	*word;
	char	*start;

	start = line;
	while (*line && is_word(line))
		line++;
	word = strndup(start, line - start);
	printf("word: %s\n", word);
	if (word == NULL)
		fatal_error("strndup");
	*rest_line = line;
	return (create_new_token_list(word, TK_WORD));
}

t_token *create_new_token_list(char *word, t_token_kind kind)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		fatal_error("malloc");
	new_token->word = word;
	new_token->kind = kind;
	new_token->next = NULL;
	return (new_token);
}

t_token	*tokenize(char	*line)
{
	t_token	head;
	t_token	*token;

	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (is_blank(*line))
			skip_blank(&line, line);
		if (is_operator(line))
		{
			token->next = add_operator_to_list(&line, line);
			// token = token->next;
		}
		else if (is_word(line))
		{
			token->next = add_word_to_list(&line, line);
			// token = token->next;
		}
		else
			assert_error("Unexpected Token");
		token = token->next;
	}
	token->next = create_new_token_list(NULL, TK_EOF);
	return (head.next);
}

static char	**tail_recursive(t_token *tok, int nargs, char **argv)
{
	if (tok == NULL || tok->kind == TK_EOF)
		return (argv);
	argv = reallocf(argv, (nargs + 2) * sizeof(char *));
	argv[nargs] = strdup(tok->word);
	if (argv[nargs] == NULL)
		fatal_error("strdup");
	argv[nargs + 1] = NULL;
	return (tail_recursive(tok->next, nargs + 1, argv));
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;

	argv = calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	return (tail_recursive(tok, 0, argv));
}
