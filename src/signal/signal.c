/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuohno <yuohno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:30:00 by yuohno            #+#    #+#             */
/*   Updated: 2023/05/30 18:23:50 by yuohno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sig = 0;

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
	// printf("handle_signal\n");
	// fflush(stdout);
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
		// printf("hello!\n");
		// fflush(stdout);
		// rl_crlf();
		// sleep(1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		// printf("sig: %d\n", sig);
		rl_done = 1;
		// printf("sig: %d\n", sig);
	}
	return (0);
}

void	set_signal(void)
{
	extern int	_rl_echo_control_chars;

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
