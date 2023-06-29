/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:36:49 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/21 20:19:49 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	*base;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	base = "0123456789";
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	write(fd, &base[n % 10], 1);
}

// #include <stdio.h>
// int main()
// {
// 	int i = INT32_MIN;
// 	printf("%d\n",i*-1);
// 	return 0;
// }