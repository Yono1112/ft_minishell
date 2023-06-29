/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:30:28 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/28 11:57:17 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	unsigned char	u_ch;
	unsigned char	*u_buf;

	u_ch = (unsigned char)ch;
	u_buf = (unsigned char *)buf;
	if (n == 0)
		return (0);
	while (n-- != 0)
	{
		if (*u_buf == u_ch)
			return ((void *)(u_buf));
		u_buf++;
	}
	return (0);
}
// #include <libc.h>
// int main(void)
// {
// 	int i = 0;
// 	char a[] = "1234567890";//
// 	char b = 'z';//search
// 	char *c;

// 	c = ft_memchr(a,b,30);//my_ft
// 	printf("%p\n",c);

// 	c = memchr(a,b,30);
// 	printf("%p\n",c);//ori_ft
// 	return (0);
// }
