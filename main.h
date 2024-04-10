/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:18:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/10 13:51:36 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdint.h>
# include <string.h>
# include "./execution/execution.h"
# include "./parsing/parsing.h"
# include "./builtin/builtin.h"
# include "./signal_handling/signals.h"

# define HOSTNAME_FILE "/etc/hostname"
# define HOSTNAME_LENGTH 256

#endif
