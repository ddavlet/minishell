/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:18:40 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/20 11:39:47 by ddavlety         ###   ########.fr       */
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
# include <readline/readline.h>

# define HOSTNAME_FILE "/proc/sys/kernel/hostname"
# define HOSTNAME_LENGTH 256

char	*get_relative_pwd(t_env *env);
char	*hostname(void);
int		is_subshell(int argc, char **argv);
char	*shell_prompt(t_env *shell_env);
t_env	*initialize_shell(const char *envp[]);
char	*create_prompt(t_env *shell_env);

#endif
