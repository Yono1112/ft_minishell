/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:19:11 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/26 16:25:06 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char *line)
{
	char *const	operators[] = {">>", "<<", ">", "<",
		"||", "|", "&", "&&", ";", ";;", "(", ")", "\n"};
	size_t				i;
	size_t				operators_len;

	i = 0;
	operators_len = sizeof(operators) / sizeof(*operators);
	while (i < operators_len)
	{
		if (!ft_strncmp(line, operators[i], ft_strlen(operators[i])))
			return (true);
		i++;
	}
	return (false);
}

t_token	*add_operator_to_list(char **rest_line, char *line)
{
	char *const	operators[] = {">>", "<<", ">", "<",
		"||", "|", "&&", "&", ";;", ";", "(", ")", "\n"};
	size_t				i;
	size_t				operators_len;
	char				*operator;
	char				*str;

	i = 0;
	operators_len = sizeof(operators) / sizeof(*operators);
	while (i < operators_len)
	{
		operator = operators[i];
		if (!ft_strncmp(line, operators[i], ft_strlen(operator)))
		{
			*rest_line = line + ft_strlen(operator);
			str = ft_strndup(line, ft_strlen(operator));
			if (!str)
				fatal_error("ft_strndup");
			return (create_new_token_list(str, TK_OP));
		}
		i++;
	}
	fatal_error("Unexpected operator");
	return (NULL);
}
