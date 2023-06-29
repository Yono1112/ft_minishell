/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:28:51 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/28 12:03:55 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *b, const char *l, size_t n)
{
	unsigned char	*big;
	unsigned char	*little;
	size_t			i;
	size_t			j;

	big = (unsigned char *)b;
	little = (unsigned char *)l;
	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (i < n && big[i] != 0)
	{
		j = 0;
		while (i < n - j && big[i + j] == little[j])
		{
			j++;
			if (little[j] == 0)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
// #include <libc.h>
// int main(void)
// {

// 	char a[] = "libft-test-tokyo";//
// 	char b[] = "test";//search
// 	char *c;
// 	int k = 10;

// 	c = ft_strnstr(a,b,k);//my_ft
// 	printf("%p\n",c);

// 	c = strnstr(a,b,k);
// 	printf("%p\n",c);//ori_ft
// 	return (0);
// }