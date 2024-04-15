/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:30:41 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/15 17:41:41 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static void	handle_sigint_shell_input(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_execution(int signum)
{
	g_signal = signum;
	// printf("pid of signal handler%d\n", getpid());
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

static void	handle_sigquit_execution(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "Quit (core dumped)", 18);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	configure_signals_shell_input(void)
{
	signal(SIGINT, handle_sigint_shell_input);
	signal(SIGQUIT, SIG_IGN);
}

void	configure_signals_execution(void)
{
	signal(SIGINT, handle_sigint_execution);
	signal(SIGQUIT, handle_sigquit_execution);
}
