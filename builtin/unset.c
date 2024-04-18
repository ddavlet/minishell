/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:59 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:35:00 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(const char **argv, t_env *shell_env)
{
	uint32_t	i;

	i = 1;
	while (argv[i])
		unset_envvar(shell_env, argv[i++]);
	return (0);
}
