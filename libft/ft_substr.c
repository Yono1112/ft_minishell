/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:15:07 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/13 22:50:28 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*re;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	if (ft_strlen(s) - (size_t)start < len)
		re = malloc(ft_strlen(s) - (size_t)start + 1);
	else
		re = malloc(len + 1);
	if (re == NULL)
		return (NULL);
	while (len != 0 && s[i] != '\0')
	{
		re[i] = s[start + i];
		i++;
		len--;
	}
	re[i] = '\0';
	return (re);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", ft_substr("asdfghjkl", 0, 4));
// 	return (0);
// }