/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:30:00 by yuohno            #+#    #+#             */
/*   Updated: 2023/06/01 18:55:33 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sig = 0;
extern int	_rl_echo_control_chars;

void	reset_signal(void)
{
	// printf("reset_signal\n");
	// printf("sig: %d\n", sig);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	handle_signal(int signal_num)
{
	sig = signal_num;
}

// void	handle_signal(int signal_num)
// {
// 	(void)signal_num;
// 		// sig = 0;
// 		// readline_interrupted = true;
// 		rl_replace_line("", 0);
// 		// rl_crlf();
// 		rl_on_new_line();
// 		rl_redisplay();
// 		rl_done = 1;
// }

int	check_state(void)
{
	// if (sig == 0)
	//   	return (0);
	if (sig == SIGINT)
	{
		// printf("sig: %d\n", sig);
		sig = 0;
		// printf("sig: %d\n", sig);
		readline_interrupted = true;
		// rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
		rl_done = 1;
		// rl_crlf();
		// printf("\n");
	}
	return (0);
}

void	set_signal(void)
{
	_rl_echo_control_chars = NOT_CONTROL_CHARS;
	// _rl_echo_control_chars = 1;
	// rl_outstream = stdout;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		fatal_error("signal");
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		fatal_error("signal");
}
