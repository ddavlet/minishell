/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:30:41 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/24 11:11:39 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigusr_handler(int signo, siginfo_t *info, void *scope)
{
	(void)scope;
	(void)info;
	if (signo == SIGQUIT)
	{
		write(1, "\033[K", 3);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// signals1();
}

void	sigusr_handler2(int signo, siginfo_t *info, void *scope)
{
	if (info->si_pid == getpid())
		exit(0) ;
	(void)scope;
	(void)info;
	if (signo == SIGQUIT)
	{
		write(1, "\n", 1);
		// write(1, "\033[K", 3);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		// write(1, "\033[K", 3);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	// signals1();
}

int	signals(pid_t pid)
{
	(void)pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigusr_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGQUIT");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGINT");
	return (0);
}


int	signals2(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigusr_handler2;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGQUIT");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGINT");
	return (0);
}
