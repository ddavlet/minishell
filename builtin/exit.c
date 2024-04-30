/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:47 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/30 10:13:18 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	free_exit(int exit_code, t_cmd2 *cmds, t_env *shell_env)
{
	free_cmds(cmds);
	free_env(shell_env);
	exit (exit_code);
}

int	builtin_exit(const char **argv, t_cmd2 *cmds, t_env *shell_env)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	ft_putendl_fd("exit", 1);
	if (i > 1)
	{
		if (!ft_isnumber((char *)argv[1]))
		{
			ft_putstr_fd("minshell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required", 2);
			free_exit(2, cmds, shell_env);
		}
		if (i > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
		i = ft_atoi(argv[1]);
		free_exit(i % 256, cmds, shell_env);
	}
	free_exit(EXIT_SUCCESS, cmds, shell_env);
	return (EXIT_SUCCESS);
}
