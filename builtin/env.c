/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:44 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:34:46 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(const char **argv, t_env *shell_env)
{
	uint32_t	i;

	i = 0;
	if (argv[1])
		return (builtin_err_gen("env", \
		"option(s) or argument(s) are not allowed", NULL));
	while (shell_env->envp[i])
		ft_putendl_fd(shell_env->envp[i++], STDOUT_FILENO);
	return (0);
}
