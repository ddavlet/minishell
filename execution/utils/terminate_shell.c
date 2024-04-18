/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:53 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:31:54 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	terminate_shell(t_env *shell_env, int exit_status, char *msg)
{
	if (shell_env)
		free_env(shell_env);
	if (msg)
	{
		if (exit_status != 0)
			ft_putendl_fd(msg, STDERR_FILENO);
		else
			ft_putendl_fd(msg, STDOUT_FILENO);
	}
	exit(exit_status);
}
