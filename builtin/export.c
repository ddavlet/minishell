/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:50 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/26 13:30:18 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	set_flag(const char *name, t_env *shell_env)
{
	t_env	*child;

	if (!name)
		return ;
	child = shell_env->child;
	while (child)
	{
		if (child->letter == *name && *(name + 1))
		{
			child = child->child;
			name++;
		}
		else if (child->letter == *name && !*(name + 1))
		{
			child->exported = true;
			return ;
		}
		else
			child = child->next;
	}
}

int	builtin_export(const char **argv, t_env *shell_env)
{
	uint32_t	i;
	char		*key;
	char		*value;
	char		**env_print;

	i = 1;
	while (argv[i] != NULL)
	{
		key = ft_strcdup(argv[i], '=');
		value = ft_strchr(argv[i], '=');
		if (value == NULL)
		{
			append_envp(shell_env, key, value);
			set_flag(key, shell_env);
			free(key);
			return (0);
		}
		value++;
		append_envp(shell_env, key, value);
		free(key);
		i++;
	}
	if (!argv[1])
	{
		i = 0;
		env_print = init_export_print(shell_env);
		while (env_print[i])
			ft_putendl_fd(env_print[i++], STDOUT_FILENO);
		free_ptr_str(env_print);
	}
	return (0);
}
