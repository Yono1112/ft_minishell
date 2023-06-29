/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:35:31 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 14:47:27 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **s, char c)
{
	size_t	len;
	char	*appended_word;

	len = 2;
	if (*s)
		len += ft_strlen(*s);
	appended_word = (char *)malloc(len);
	if (appended_word == NULL)
		fatal_error("malloc");
	if (*s)
	{
		ft_strlcpy(appended_word, *s, len);
		free(*s);
	}
	appended_word[len - 1] = '\0';
	appended_word[len - 2] = c;
	*s = appended_word;
}
