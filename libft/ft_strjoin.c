/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:02:58 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/06 21:53:30 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*chap;
	char	*save;

	if (!s1 || !s2)
		return (NULL);
	chap = (char *)malloc(ft_strlen(s1) + ft_strlen(s2)+1);
	if (!chap)
		return (NULL);
	save = chap;
	while (*s1 != '\0')
		*chap++ = *s1++;
	while (*s2 != '\0')
		*chap++ = *s2++;
	*chap = '\0';
	return (save);
}
// #include<stdlib.h>
// int main(void)
// {
// 	printf("%s",ft_strjoin("hello", "world"));
// 	return (0);
// }
// ""  NULL '\0' 0
// 		""
// 		char str1[] = "456"; //[1][2][3][\0]
// 		char str2[] = "123"; //[1][2][3][\0]
// 		char *str = ""; //[\0][]
// 		NULL
// 		char *str = NULL; //
// 		char str = malloc //[][][][]
// 		'\0'
// 		char c = '\0' //'\0'
