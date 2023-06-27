/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:21:28 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 04:54:09 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

static char	*append_variable_name(char **rest, char *current_word)
{
	char	*variable_name;

	variable_name = ft_calloc(1, sizeof(char));
	if (variable_name == NULL)
		fatal_error("ft_calloc");
	if (!is_alpha_under(*current_word))
		fatal_error(
			"Variable must starts with alphabetic character or underscore.");
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

void	expand_variable_str(char **new_word, char **rest,
			char *current_word, t_env **env)
{
	char	*name;
	char	*value;

	if (*current_word != '$')
		fatal_error("Expected dollar sign");
	current_word++;
	name = append_variable_name(&current_word, current_word);
	value = ft_getenv(name, env);
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
