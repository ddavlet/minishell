/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:10 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:29:46 by ddavlety         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_signal;

/*Configurations*/
void		configure_signals_shell_input(void);
void		configure_signals_execution(void);
void		configure_signals_heardoc(void);

/*Handlers*/
void		handle_sigint_shell_input(int signum);
void		handle_sigint_execution(int signum);
void		handle_sigint_hear_doc(int signum);
void		handle_sigquit_execution(int signum);

#endif
