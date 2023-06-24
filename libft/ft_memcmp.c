/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:57:27 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/13 20:53:46 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t n)
{
	unsigned char	*buf1;
	unsigned char	*buf2;

	buf1 = (unsigned char *)b1;
	buf2 = (unsigned char *)b2;
	if (n == 0)
		return (0);
	while (n-- != 0)
	{
		if (*buf1 != *buf2)
			return ((int)(*buf1 - *buf2));
		buf1++;
		buf2++;
	}
	return (0);
}

// #include <libc.h>
// int main(void)
// {
// 	int i = 0;
// 	char a[] = "abcd";//
// 	char b[] = "xyz";//search
// 	int c ;
// 	int k = 2;

// 	c = ft_memcmp(a,b,k);//my_ft
// 	printf("%d\n",c);

// 	c = memcmp(a,b,k);
// 	printf("%d\n",c);//ori_ft
// 	return (0);
// }