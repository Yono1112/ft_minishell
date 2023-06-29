/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 02:38:13 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/26 03:56:32 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *b1, const void *b2, size_t n)
{
	size_t		i;
	char		*buf1;
	const char	*buf2;

	buf2 = b2;
	if (b1 == b2 || n == 0)
		return (b1);
	buf1 = b1;
	i = 0;
	if (buf1 < buf2)
	{
		while (i < n)
		{
			buf1[i] = buf2[i];
			i++;
		}
	}
	else if (buf1 > buf2)
		while (i < n--)
			buf1[n] = buf2[n];
	return (buf1);
}
