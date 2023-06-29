/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 05:19:35 by rnaka             #+#    #+#             */
/*   Updated: 2023/06/27 05:19:40 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	char	*s;

	s = dst;
	while (*s)
		s++;
	while (len > 0 && *src)
	{
		*s = *src;
		s++;
		src++;
		len--;
	}
	*s = '\0';
	return (dst);
}
