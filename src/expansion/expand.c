/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:13:20 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/24 07:20:14 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	len;
	char	*new;

	if (*s)
		len = strlen(*s) + 2;
	else
		len = 2;
	new = malloc(len);
	if (!new)
		fatal_error("malloc");
	if (*s)
		strncpy(new, *s, len);
	new[len - 2] = c;
	new[len - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	expand(t_node *node, t_env **env)
{
	expand_variable(node, env);
	// print_token(node->command->args);
	split_word(node, env);
	remove_quote(node, env);
}
