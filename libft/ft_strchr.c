/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:07:32 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/10 17:49:35 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*u_str;
	unsigned char	u_ch;

	i = 0;
	u_ch = (unsigned char)c;
	u_str = (unsigned char *)s;
	if (u_str[i] == u_ch)
		return ((char *)u_str);
	while (u_str[i++] != 0)
		if (u_str[i] == u_ch)
			return ((char *)(u_str + i));
	return (NULL);
}

// #include <libc.h>
// int main(void)
// {
// 	int i = 0;
// 	char a[] = "1234567890";//
// 	char b = '6';//search
// 	char *c;

// 	c = ft_strchr(a,b);//my_ft
// 	printf("%s\n",c);

// 	c = strchr(a,b);
// 	printf("%s\n",c);//ori_ft
// 	return (0);
// }