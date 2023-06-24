/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:31:30 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/26 04:22:28 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*keep;
	unsigned char	let;

	keep = NULL;
	let = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	if (str[i] == let)
		keep = str;
	while (str[i] != '\0')
	{
		if (str[i] == let)
			keep = str + i;
		i++;
	}
	if (str[i] == let)
		keep = str + i;
	return ((char *)keep);
}
// #include <libc.h>
// int main(void)
// {
// 	int i = 0;
// 	char a[] = "123qew";//
// 	char b = 'w'+256;//search
// 	char *c;

// 	c = ft_strrchr(a,b);//my_ft
// 	printf("%p\n",c);

// 	c = strrchr(a,b);
// 	printf("%p\n",c);//ori_ft
// 	return (0);
// }