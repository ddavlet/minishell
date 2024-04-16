/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:39:17 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/14 15:25:38 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/signal.h>
# include <sys/unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void	configure_signals_shell_input(void);
void	configure_signals_execution(void);
void	configure_signals_heardoc(void);

extern int	g_signal;

#endif
