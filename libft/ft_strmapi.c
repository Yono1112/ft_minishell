/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:25 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/21 19:26:56 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const*s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*ret;

	len = 0;
	i = 0;
	if (s == 0)
		return (NULL);
	len = ft_strlen(s);
	if (f == 0)
		return (NULL);
	ret = malloc(len + 1);
	if (ret == NULL)
		return (ret);
	while (i < len)
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

// char	touppera(unsigned int i, char c)
// {
// 	if ('a' <= c && c <= 'z')
// 	{
// 		c = ft_toupper(c);
// 		c += i;
// 	}
// 	return (c);
// }
// # include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", ft_strmapi("aaaaaaaaaaaaAA", touppera));
// 	return (0);
// }

// int main()
// {
// 	char tmp[] = "12345";
// 	char *t;
// 	t = ft_strmapi(tmp,NULL);
// 	printf("%s", t);
// 	return 0;
// }