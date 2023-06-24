/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:04:10 by rnaka             #+#    #+#             */
/*   Updated: 2022/10/21 20:15:48 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	def_digit(int n)
{
	size_t	digit;

	digit = 0;
	while (n / 10 != 0)
	{
		digit++;
		n = n / 10;
	}
	digit++;
	return (digit);
}

static size_t	ft_mult(size_t digit)
{
	size_t	ing;

	ing = 1;
	while (digit--)
		ing *= 10;
	return (ing);
}

char	*allocator(int flag, size_t digit, char **restr)
{
	if (flag)
		*restr = ft_calloc(digit + 2, sizeof(char));
	else
		*restr = ft_calloc(digit + 1, sizeof(char));
	return (*restr);
}

char	*fill_digit(int flag, char *restr, size_t digit, int n)
{
	size_t	i;

	i = 0;
	if (flag)
		restr[i++] = '-';
	while (digit / 10 != 0)
	{
		restr[i++] = n / digit + '0';
		n = n % digit;
		digit = digit / 10;
	}
	restr[i] = n + '0';
	return (restr);
}

char	*ft_itoa(int n)
{
	char	*restr;
	size_t	flag;
	size_t	digit;

	flag = 0;
	if (n < 0)
	{
		flag = 1;
		n *= -1;
	}
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digit = def_digit(n);
	if (allocator(flag, digit, &restr) == NULL)
		return (NULL);
	digit--;
	digit = ft_mult(digit);
	return (fill_digit(flag, restr, digit, n));
}
// int main()
// {
// 	int m = -2147483648;
// 	printf("m:%s",ft_itoa(m));
// 	return 0;
// }//restr = fill_digit(flag, restr, digit);
	/*	s = 0;
	if (flag)
		restr[s++] = '-';
	while (digit / 10 != 0)
	{
		restr[s++] = n / digit + '0';
		n = n % digit;
		digit = digit / 10;
	}
	restr[s++] = n + '0';
	*/