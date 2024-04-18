/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:06:42 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:10:14 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handle_sigint_shell_input(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_execution(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	handle_sigint_hear_doc(int signum)
{
	g_signal = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	close(0);
}

void	handle_sigquit_execution(int signum)
{
	g_signal = signum;
	write(STDOUT_FILENO, "Quit (core dumped)", 18);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}
