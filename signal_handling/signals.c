/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:30:41 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:06:55 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

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
