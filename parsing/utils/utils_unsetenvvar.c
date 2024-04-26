/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unsetenvvar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:37 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/26 12:21:18 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	remove_envvar(t_env	*shell_env, const char *name)
{
	t_env	*child;

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
			if (child->exists == true)
			{
				free(child->content);
				child->exists = false;
			}
			child->exported = false;
			return (0);
		}
		else
			child = child->next;
	}
	return (1);
}

int	unset_envvar(t_env *shell_env, const char *to_find)
{
	if (!to_find)
		return (1);
	if (remove_envvar(shell_env, to_find))
		return (0);
	else
	{
		free_ptr_str(shell_env->envp);
		shell_env->envp = init_envv(shell_env);
		if (!shell_env->envp)
		{
			write(2, "minishell: memory allocation error occured", 42);
			exit(255);
		}
	}
	return (0);
}
