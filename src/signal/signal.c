/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:30:00 by yuohno            #+#    #+#             */
/*   Updated: 2023/05/28 21:08:40 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signal_num)
{
	if (signal_num != SIGINT)
		return ;
	// printf("Ctrl + C\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
