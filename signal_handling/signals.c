/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:30:41 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/21 14:25:51 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigusr_handler(int signo, siginfo_t *info, void *scope)
{

	(void)scope;
	(void)info;
	printf("%s", (char *)scope);
	if (signo == SIGQUIT)
	{
		write(1, "\033[K", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	signals1();
}

int	signals1(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigusr_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGUSR1");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGUSR2");
	return (0);
}


int	signals2(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigusr_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGUSR1");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_printf("Error recieving SIGUSR2");
	return (0);
}
