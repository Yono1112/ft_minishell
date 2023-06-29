/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:05:26 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/29 13:28:41 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(char c, int sign, long result)
{
	if (sign == 1 && (result > LONG_MAX / 10 || (result == LONG_MAX / 10
				&& c - '0' > LONG_MAX % 10)))
		return (1);
	if (sign == -1 && (result > LONG_MAX / 10 || (result == LONG_MAX / 10
				&& c - '0' > LONG_MAX % 10 + 1)))
		return (1);
	return (0);
}

long	ft_atol(const char *str, int *is_over_long)
{
	int		sign;
	long	result;
	int		i;

	i = 0;
	sign = 1;
	result = 0;
	while ((('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		if (sign == 1 && check_overflow(str[i], sign, result))
		{
			*is_over_long = 1;
			return (LONG_MAX);
		}
		if (sign == -1 && check_overflow(str[i], sign, result))
		{
			*is_over_long = 1;
			return (LONG_MIN);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
