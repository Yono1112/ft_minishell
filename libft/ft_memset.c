/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:57:58 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/26 04:27:29 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	int				i;
	unsigned char	*u_buf;

	u_buf = (unsigned char *)buf;
	i = 0;
	while (0 < n)
	{
		u_buf[i] = (unsigned char)ch;
		n--;
		i++;
	}
	return (buf);
}
