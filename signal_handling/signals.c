/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:30:41 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/04 16:40:26 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigusr_handler(int signo, siginfo_t *info, void *scope)
{

	(void)scope;
	if (signo == SIGQUIT)
		write(1, "signal SIGQUIT recieved", 23);
	if (signo == SIGINT)
		write(1, "signal SIGINT recieved", 23);

		// kill(info->si_pid, SIGUSR1);
}

// int	main(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = sigusr_handler;
// 	sigemptyset(&sa.sa_mask);
// 	if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 		ft_printf("Error recieving SIGUSR1");
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 		ft_printf("Error recieving SIGUSR2");
// 	ft_printf("%i\n", getpid());
// 	while (1)
// 		usleep(1);
// 	return (0);
// }
