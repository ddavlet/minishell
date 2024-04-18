/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:50 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:34:51 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// "export %s=%s\n", <name>, <value>

int	builtin_export(const char **argv, t_env *shell_env) // recieve code!
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
