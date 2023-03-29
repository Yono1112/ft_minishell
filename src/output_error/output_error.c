/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:09:29 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/29 03:29:05 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *str)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", str);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *str)
{
	dprintf(STDERR_FILENO, "Assert Error: %s\n", str);
	exit(255);
}
