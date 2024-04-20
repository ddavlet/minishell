/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:50 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/20 11:46:01 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_export(const char **argv, t_env *shell_env)
{
	uint32_t	i;
	char		*key;
	char		*value;

	i = 1;
	while (argv[i] != NULL)
	{
		key = ft_strcdup(argv[i], '=');
		value = ft_strchr(argv[i], '=');
		if (value == NULL)
		{
			free(key);
			return (1);
		}
		value++;
		append_envp(shell_env, key, value);
		free(key);
		i++;
	}
	return (0);
}
