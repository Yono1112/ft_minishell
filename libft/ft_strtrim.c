/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:56:08 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/13 22:49:10 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	front_trim(char const *s1, char const *set)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (j != ft_strlen(set))
	{
		if (s1[i] == set[j++])
		{
			j = 0;
			i++;
		}
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	i = front_trim(s1, set);
	j = 0;
	s1 += i;
	if (ft_strlen(s1) == 0)
		return (ft_calloc(1, 1));
	i = ft_strlen(s1);
	while (j < ft_strlen(set) && i > 1)
	{
		if (s1[i - 1] == set[j++])
		{
			j = 0;
			i--;
		}
	}
	newstr = ft_calloc(1, i + 1);
	if (!newstr)
		return (NULL);
	ft_memmove(newstr, s1, i);
	return (newstr);
}

// #include <stdio.h>
// int main()
// {
// 	char ss[]= "aadfgfghjklaaaasdfghjka";
// 	char ff[]= "a";
// 	printf("%s",ft_strtrim(ss,ff));
// 	return (0);
// }