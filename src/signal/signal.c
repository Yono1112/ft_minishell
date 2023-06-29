/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:30:00 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/29 15:25:57 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_signal_to_default(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

static void	handle_signal(int signal_num)
{
	g_data.sig = signal_num;
}

static int	check_state(void)
{
	if (g_data.sig == SIGINT)
	{
		g_data.sig = 0;
		g_data.heredoc_sig_received = true;
		rl_replace_line("", 0);
		rl_done = 1;
		g_data.last_status = 1;
	}
	return (0);
}

void	set_signal_action(void)
{
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		fatal_error("signal");
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		fatal_error("signal");
}
