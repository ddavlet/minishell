/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:18:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/10 14:27:16 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "./builtin/builtin.h"
# include "./execution/execution.h"
# include "./parsing/parsing.h"
# include "./signal_handling/signals.h"
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

# define HOSTNAME_FILE "/proc/sys/kernel/hostname"
# define HOSTNAME_LENGTH 256

char	*get_relative_pwd(t_env *env);
char	*hostname(void);
int		is_subshell(int argc, char **argv);
void	terminate_shell(t_env *shell_env, int exit_status, char *msg);

#endif
