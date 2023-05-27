/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:57:57 by yuohno            #+#    #+#             */
/*   Updated: 2023/05/27 17:43:35 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metacharacter(char c)
{
	if (is_blank(c))
		return (true);
	return (c && strchr("|&;()<>\n", c));
}

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_under(s[1]));
}

bool	is_special_parametar(char *str)
{
	return (str[0] == '$' && str[1] == '?');
}

bool	is_quote_after_dollar(char *str)
{
	return (str[0] == '$' && (str[1] == SINGLE_QUOTE_CHAR || str[1] == DOUBLE_QUOTE_CHAR));
}

void	append_num(char **new_word, unsigned int num)
{
	if (num == 0)
		append_char(new_word, '0');
	else
	{
		if (num / 10 != 0)
			append_num(new_word, num / 10);
		append_char(new_word, (num % 10) + '0');
	}
}

void	expand_parameter_str(char **new_word, char **rest, char *current_word)
{
	if (!is_special_parametar(current_word))
		assert_error("Expected special parameter");
	current_word += 2;
	append_num(new_word, last_status);
	*rest = current_word;
}

char	*append_variable_name(char **rest, char *current_word)
{
	char	*variable_name;

	variable_name = calloc(1, sizeof(char));
	if (variable_name == NULL)
		fatal_error("calloc");
	if (!is_alpha_under(*current_word))
		assert_error("Variable must starts with alphabetic character or underscore.");
	append_char(&variable_name, *current_word);
	current_word++;
	while (is_alpha_num_under(*current_word))
	{
		append_char(&variable_name, *current_word);
		current_word++;
	}
	*rest = current_word;
	return (variable_name);
}

void	expand_variable_str(char **new_word, char **rest, char *current_word)
{
	char	*name;
	char	*value;

	if (*current_word != '$')
		assert_error("Expected dollar sign");
	current_word++;
	name = append_variable_name(&current_word, current_word);
	value = getenv(name);
	if (value != NULL)
	{
		while (*value)
		{
			append_char(new_word, *value);
			value++;
		}
	}
	free(name);
	*rest = current_word;
}

void	append_single_quote(char **new_word, char **rest, char *current_word)
{
	if (*current_word == SINGLE_QUOTE_CHAR)
	{
		append_char(new_word, *current_word);
		current_word++;
		while (*current_word != SINGLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				assert_error("Unclosed single quote");
			append_char(new_word, *current_word++);
		}
		append_char(new_word, *current_word);
		current_word++;
		*rest = current_word;
	}
	else
		assert_error("Expected single quote");
}

void	append_double_quote(char **new_word, char **rest, char *current_word)
{
	if (*current_word == DOUBLE_QUOTE_CHAR)
	{
		append_char(new_word, *current_word);
		current_word++;
		while (*current_word != DOUBLE_QUOTE_CHAR)
		{
			if (*current_word == '\0')
				assert_error("Unclosed double quote");
			else if (is_variable(current_word))
				expand_variable_str(new_word, &current_word, current_word);
			else if (is_special_parametar(current_word))
				expand_parameter_str(new_word, &current_word, current_word);
			else
				append_char(new_word, *current_word++);
		}
		append_char(new_word, *current_word);
		current_word++;
		*rest = current_word;
	}
	else
		assert_error("Expected double quote");
}

void	expand_variable_token(t_token *token)
{
	char	*new_word;
	char	*current_word;

	// printf("start expand_variable_token\n");
	while (token != NULL && token->kind == TK_WORD && token->word != NULL)
	{
		// printf("token_kind: %d\n", token->kind);
		// printf("token_word: %s\n", token->word);
		current_word = token->word;
		new_word = calloc(1, sizeof(char));
		if (new_word == NULL)
			fatal_error("calloc");
		while (*current_word && !is_metacharacter(*current_word))
		{
			if (*current_word == SINGLE_QUOTE_CHAR)
				append_single_quote(&new_word, &current_word, current_word);
			else if (*current_word == DOUBLE_QUOTE_CHAR)
				append_double_quote(&new_word, &current_word, current_word);
			else if (is_variable(current_word))
				expand_variable_str(&new_word, &current_word, current_word);
			else if (is_special_parametar(current_word))
				expand_parameter_str(&new_word, &current_word, current_word);
			else if (is_quote_after_dollar(current_word))
				current_word++;
			else
				append_char(&new_word, *current_word++);
		}
		free(token->word);
		token->word = new_word;
		token = token->next;
	}
	// printf("finish expand_variable_token\n");
}

void	expand_variable(t_node *node)
{
	// printf("start expand_variable\n");
	while (node != NULL)
	{
		// printf("node->kind: %d\n", node->kind);
		// if (node->next != NULL)
		// 	node = node->next;
		if (node->command != NULL)
		{
			// printf("expand command\n");
			expand_variable_token(node->command->args);
		}
		if (node->command->redirects != NULL)
		{
			// printf("expand redirects\n");
			expand_variable_token(node->command->redirects->filename);
		}
		node = node->next;
		// printf("finish expand_variable\n");
	}
}

// void	expand_variable_str(char **new_word, char **rest, char *current_word)
// {
// 	char	*name;
// 	char	*value;
// 
// 	name = calloc(1, sizeof(char));
// 	if (name == NULL)
// 		fatal_error("calloc");
// 	if (*current_word != '$')
// 		assert_error("Expected dollar sign");
// 	current_word++;
// 	if (!is_alpha_under(*current_word))
// 		assert_error("Variable must starts with alphabetic character or underscore.");
// 	append_char(&name, *current_word);
// 	current_word++;
// 	while (is_alpha_num_under(*current_word))
// 	{
// 		append_char(&name, *current_word);
// 		current_word++;
// 	}
// 	value = getenv(name);
// 	free(name);
// 	if (value)
// 	{
// 		while (*value)
// 		{
// 			append_char(new_word, *value);
// 			value++;
// 		}
// 	}
// 	*rest = current_word;
// }

// void	expand_variable_token(t_token *tok)
// {
// 	char	*new_word;
// 	char	*p;
// 
// 	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
// 		return ;
// 	p = tok->word;
// 	new_word = calloc(1, sizeof(char));
// 	if (new_word == NULL)
// 		fatal_error("calloc");
// 	while (*p && !is_metacharacter(*p))
// 	{
// 		if (*p == SINGLE_QUOTE_CHAR)
// 			append_single_quote(&new_word, &p, p);
// 		else if (*p == DOUBLE_QUOTE_CHAR)
// 			append_double_quote(&new_word, &p, p);
// 		else if (is_variable(p))
// 			expand_variable_str(&new_word, &p, p);
// 		else
// 			append_char(&new_word, *p++);
// 	}
// 	free(tok->word);
// 	tok->word = new_word;
// 	expand_variable_token(tok->next);
// }

// void	expand_variable(t_node *node)
// {
// 	if (node == NULL)
// 		return ;
// 	printf("node->kind: %d\n", node->kind);
// 	expand_variable_token(node->args);
// 	expand_variable_token(node->filename);
// 	// do not expand heredoc delimiter
// 	expand_variable(node->redirects);
// 	expand_variable(node->command);
// 	expand_variable(node->next);
// }

