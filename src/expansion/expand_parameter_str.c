/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:23:58 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/27 03:24:08 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_num(char **new_word, unsigned int num)
{
	if (num == 0)
		append_char(new_word, '0');
	else
	{
		if (num / 10 != 0)
			append_num(new_word, num / 10);
		append_char(new_word, (num % 10) + '0');
	}
}

void	expand_parameter_str(char **new_word, char **rest, char *current_word)
{
	if (!is_special_parametar(current_word))
		fatal_error("Expected special parameter");
	current_word += 2;
	append_num(new_word, g_data.last_status);
	*rest = current_word;
}
