/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:18:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/21 12:16:59 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include <readline/history.h>
# include <stddef.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdint.h>
# include <string.h>
# include "./execution/execution.h"
# include "./builtin/builtin.h"
# include "./signal_handling/signals.h"


# define HOSTNAME_FILE "/etc/hostname"
# define HOSTNAME_LENGTH 256

#endif
