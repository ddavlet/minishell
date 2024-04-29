/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:50 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 14:42:02 by ddavlety         ###   ########.fr       */
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

static int	write_error(char *name, char *value)
{
	write(2, "minishell: export: ", 19);
	write(2, name, ft_strlen(name));
	if (value)
		write(2, value, ft_strlen(value));
	write(2, ": not a valid identifier\n", 25);
	return (1);
}

static int	check_append(char *name, char *value, t_env *shell_env)
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
		set_flag(value, shell_env);
	return (0);
}

static int	export_argument(const char **argv, t_env *shell_env)
{
	uint32_t	i;
	char		*key;
	char		*value;
	int			exit_code;

	exit_code = 0;
	i = 1;
	while (argv[i])
	{
		key = ft_strcdup(argv[i], '=');
		value = ft_strchr(argv[i], '=');
		if (check_append(key, value, shell_env))
			exit_code = 1;
		free(key);
		i++;
	}
	return (exit_code);
}

int	builtin_export(const char **argv, t_env *shell_env)
{
	uint32_t	i;
	char		**env_print;
	int			exit_code;

	exit_code = export_argument(argv, shell_env);
	if (!argv[1])
	{
		i = 0;
		env_print = init_export_print(shell_env);
		while (env_print[i])
			ft_putendl_fd(env_print[i++], STDOUT_FILENO);
		free_ptr_str(env_print);
	}
	return (exit_code);
}
