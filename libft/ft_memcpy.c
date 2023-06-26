/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 01:09:21 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/26 03:54:12 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *b1, const void *b2, size_t n)
{
	char		*buf1;
	const char	*buf2;

	if (!b1 && !b2)
		return (NULL);
	buf1 = b1;
	buf2 = b2;
	while (n--)
		buf1[n] = buf2[n];
	return (b1);
}
