/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:19:11 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/29 16:19:52 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char *line)
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

t_token	*add_operator_to_list(char **rest_line, char *line)
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
