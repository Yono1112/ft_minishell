/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:28:19 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/13 20:09:01 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ch;

	if (count == 0 || size == 0)
	{
		ch = malloc (1);
		if (!ch)
			return (NULL);
		*ch = '\0';
		return ((void *) ch);
	}
	if (SIZE_MAX / size < count)
		return (NULL);
	else
	{
		ch = (char *)malloc (size * count);
		if (!ch)
			return (NULL);
	}
	ft_bzero(ch, count * size);
	return ((void *)ch);
}
//23fail malloc
//26return ""
//
// # include<stdio.h>
// # include<stdlib.h>

// int	main(void)
// {
// 	char	*ch;
// 	char	*chh;

// 	ch = (char *)calloc(0,0);
// 	chh = (char *)ft_calloc(0,0);
// 	printf("%s\n",ch);
// 	printf("%gs\n",chh);
// 	free(ch);
// 	free(chh);
// 	return (0);
// }