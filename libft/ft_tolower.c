/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:48:52 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/26 04:24:53 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		c = c - 'A' + 'a';
	return (c);
}
// #include <libc.h>
// int main()
// {
// 	for (size_t i = 33; i < 150; i++)
// 	{
// 		printf("%c",ft_tolower((int)i));
// 		printf("%c\n",tolower((int)i));
// 	}
// 	return(0);
// }