/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:33:30 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/13 23:50:49 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_find_chr(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (*str && c == 0)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
			i++;
		}
		else
			i++;
	}
	return (count);
}

size_t	ft_build(char **re, char *str, char c)
{
	size_t	i;
	size_t	count;
	size_t	start;

	i = 0;
	count = 0;
	start = 0;
	re[0] = NULL;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			start = i;
			while (str[i] && str[i] != c)
				i++;
			re[count] = ft_substr(str, start, i - start);
			if (re[count] == NULL)
				return (-1);
			count++;
			re[count] = NULL;
		}
		else
			i++;
	}
	return (0);
}

char	**free_market(char **re, int count)
{
	while (1)
	{
		free(re[count]);
		if (count <= 0)
			break ;
		count--;
	}
	free(re);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**re;
	size_t	count;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_find_chr((char *)s, c);
	re = malloc(sizeof(char *) * (size + 1));
	if (re == NULL)
		return (re);
	ft_build(re, (char *)s, c);
	count = 0;
	while (count < size)
	{
		if (re[count] == NULL)
			return (free_market(re, count));
		count++;
	}
	return (re);
}
