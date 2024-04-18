/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:30:41 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 12:18:54 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static void	handle_sigint_shell_input(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
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

static void	handle_sigint_hear_doc(int signum)
{
	g_signal = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	// write(STDOUT_FILENO, "\n", 1);
	close(0);
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

void	configure_signals_heardoc(void)
{
	signal(SIGINT, handle_sigint_hear_doc);
	signal(SIGQUIT, SIG_IGN);
}
