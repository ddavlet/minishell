/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:47 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:34:49 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(const char **argv, t_cmd2 *cmds, t_env *shell_env)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
        free_env(shell_env);
        free_cmds(cmds);
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (i == 2)
	{
		if (!ft_isnumber((char *)argv[1]))
		{

			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_cmds(cmds);
			free_env(shell_env);
			exit (255);
		}
		free_env(shell_env);
		i = ft_atoi(argv[1]);
		free_cmds(cmds);
		exit(i % 256);
	}
	free_cmds(cmds);
	free_env(shell_env);
	exit (EXIT_SUCCESS);
}
