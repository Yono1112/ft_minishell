/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:30:00 by yuohno            #+#    #+#             */
/*   Updated: 2023/05/29 17:18:07 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

volatile sig_atomic_t	sig = 0;

void	reset_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	handle_signal(int signal_num)
{
	sig = signal_num;
}

int	check_state(void)
{
	// if (sig == 0)
	// 	return (0);
	if (sig == SIGINT)
	{
		sig = 0;
		// readline_interrupted = true;
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

void	set_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = NOT_CONTROL_CHARS;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
}
