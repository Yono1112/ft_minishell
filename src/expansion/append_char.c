/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:35:31 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:43:04 by yuohno           ###   ########.fr       */
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
		ft_strlcpy(new, *s, len);
	new[len - 1] = '\0';
	new[len - 2] = c;
	if (*s)
		free(*s);
	*s = new;
}
