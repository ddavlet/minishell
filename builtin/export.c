/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:50 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/26 14:34:57 by ddavlety         ###   ########.fr       */
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

static void	write_error(char *name, char *value)
{
	write(2, "minishell: export: ", 19);
	write(2, name, ft_strlen(name));
	if (value)
		write(2, value, ft_strlen(value));
	write(2, ": not a valid identifier\n", 25);
}

static void	check_append(char *name, char *value, t_env *shell_env)
{
	uint32_t	i;

	i = 0;
	if (ft_isdigit(name[0]))
	{
		return (write_error(name, value));
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (write_error(name, value));
		i++;
	}
	append_envp(shell_env, name, value);
	if (!value)
		set_flag(name, shell_env);
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
			// append_envp(shell_env, key, value);
			// set_flag(key, shell_env);
		check_append(key, value, shell_env);
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
