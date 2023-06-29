/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaka <rnaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:02:02 by rnaka             #+#    #+#             */
/*   Updated: 2022/09/28 12:06:59 by rnaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	check_over_long(int sign, unsigned long num, char c)
{
	if (sign == 1 && (LONG_MAX / 10 < num || (LONG_MAX / 10 == num && LONG_MAX
				% 10 < c - '0')))
		return (1);
	if (sign == -1 && (LONG_MAX / 10 < num || (LONG_MAX / 10 == num && LONG_MAX
				% 10 + 1 < c - '0')))
		return (-1);
	return (0);
}

int	ft_atoi(const char *s)
{
	size_t			i;
	int				sign;
	long			result;
	unsigned long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\v' || s[i] == '\f' \
				|| s[i] == '\r' || s[i] == ' ')
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
	{
		if (check_over_long(sign, num, s[i]) == 1)
			return ((int)LONG_MAX);
		if (check_over_long(sign, num, s[i]) == -1)
			return ((int)LONG_MIN);
		num = num * 10 + s[i++] - '0';
	}
	result = num * sign;
	return (result);
}

// 2147483647
// num = 314748364
// num = 214748364

// -2147483648
// int ft_atoi(const char *s)
// {
// 	int					i;
// 	int					sign;
// 	unsigned long long	num;

// 	i = 0;
// 	sign = 1;
// 	num = 0;
// 	if (s[0] == '-')
// 	{
// 		sign = -1;
// 		i++;
// 	}
// 	if (s[0] == '+')
// 		i++;
// 	// while (s[i] != 0 &&'0'<=s[i] && s[i]<='9')
// 	while (ft_isdigit(s[i]))
// 	{
// 		// if ('1'<=s[i] && s[i]<='9'&&maxmin_tester(num,s[i])==0)
// 		// {
// 		// 	if (0<zero)
// 		// 		num *=	10;
// 		// 	num += s[i]-'0';
// 		// 	zero++;
// 		// }
// 		// if (0<zero &&'0'==s[i]&&maxmin_tester(num,s[i])==0)
// 		// 	num *= 10;
// 		// if (maxmin_tester(num,s[i])==-1)
// 		// 	return((int)LONG_MIN);
// 		// if (maxmin_tester(num,s[i])==1)
// 		// 	return((int)LONG_MAX);
// 		num *=	10;
// 		num += s[i]-'0';
// 		i++;
// 	}
// 	// if (sign <0)
// 	num *= sign;
// 	return(num);
// }
