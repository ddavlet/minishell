/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:52 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/20 11:45:40 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(const char **argv, t_env *shell_env)
{
	char	*pwd;

	(void)argv;
	pwd = get_variable_value("PWD", shell_env);
	if (pwd == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory:" \
					" getcwd: cannot access parent directories:" \
					" No such file or directiory\n", 2);
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (0);
}
