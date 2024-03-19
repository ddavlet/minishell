/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:18:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/03/19 17:01:47 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include <readline/history.h>
# include <stddef.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <stdint.h>
# include <string.h>
# include <dirent.h>
# include "./libft/libft.h"
# include "./execution/execution.h"
# include "./parsing/parsing.h"
# include "./parsing/wildcard/wildcard.h"
# include "./builtin/builtin.h"


# define HOSTNAME_FILE "/etc/hostname"
# define HOSTNAME_LENGTH 256

#endif
