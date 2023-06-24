/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:13:20 by yumaohno          #+#    #+#             */
/*   Updated: 2023/06/24 22:25:50 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	len;
	char	*new;

	if (*s)
		len = ft_strlen(*s) + 2;
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
	remove_quote(node);
}
