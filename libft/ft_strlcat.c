/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 01:49:48 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/26 04:11:37 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	if (!dst && src && size == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	if (src_len < size - dst_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size] = '\0';
	}
	return (dst_len + src_len);
}
// #includeid)
// {"libft.h"
// int main(vo

// 	printf("%zu",ft_strlcat(NULL, "src2", 0));
// printf("%lu", strlcat(NULL, "src2", 0));
// 	// size_t	size;
// 	// char	dst[] = "tetete";
// 	char tmp[100] = {'\0'};
// 	tmp[0] = '1';
// 	tmp[1] = '1';
// 	tmp[2] = '1';
// 	tmp[3] = '1';
// 	tmp[10] = '1';
// 	tmp[11] = '1';
// 	tmp[12] = '1';
// 	// char src[100] = {'\0'};
// 	// src[0]='a';
// 	// src[1]='a';
// 	// src[2]='a';
// 	// src[3]='a';
// 	// src[10]='a';
// 	// src[11]='a';
// 	// src[12]='a';
// 	char *src;

// 	*src = '\0';
// if (src ==0)
// 	return (dst_len);
// 	// size = 0;
// 	// printf("%lu\n", size - ft_strlen(dst) - 1);
// 	printf("%lu\n", ft_strlcat(tmp, src, 20));
// 	// printf("%s\n",tmp);
// 	// printf("10%c\n",tmp[13]);
// 	// printf("11%c\n",tmp[14]);
// 	// printf("12%c\n",tmp[15]);
// 	// printf("%lu", strlcat("12345", "12", 5));
// 	return (0);
// }