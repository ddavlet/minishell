/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:09 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/26 12:36:07 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	add_envnode(t_env **list_p, char c, const char *content)
{
	t_env	*last;
	t_env	*new_node;

	last = *list_p;
	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return ;
	if (content)
	{
		new_node->content = ft_strdup(content);
		new_node->exists = true;
	}
	new_node->letter = c;
	if (!last)
		*list_p = new_node;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

static void	change_envnode(t_env *list_p, const char *content)
{
	if (list_p->exists)
		free(list_p->content);
	if (content)
	{
		list_p->content = ft_strdup(content);
		list_p->exists = true;
	}
	else
	{
		list_p->content = NULL;
		list_p->exists = false;
		list_p->exported = true;
	}

}

static void	add_envvar(t_env *shell_env, const char *envvar,
							const char *content)
{
	t_env	**child_p;

	child_p = &shell_env->child;
	while (*envvar)
	{
		while ((*child_p) && *envvar != (*child_p)->letter)
			child_p = &((*child_p)->next);
		if (!(*child_p) && *(envvar + 1))
		{
			add_envnode(child_p, *envvar, NULL);
			child_p = &((*child_p)->child);
		}
		else if (!(*child_p) && !*(envvar + 1))
			add_envnode(child_p, *envvar, content);
		else if (*(envvar + 1))
			child_p = &((*child_p)->child);
		else if (!*(envvar + 1))
		{
			// if ((*child_p)->exists)
			// 	free((*child_p)->content);
			// (*child_p)->content = ft_strdup(content);
			// (*child_p)->exists = true;
			change_envnode(*child_p, content);
		}
		envvar++;
	}
}

t_env	*init_env(const char **envp)
{
	t_env		*shell_env;
	uint32_t	i;
	uint32_t	j;
	char		*tmp;

	shell_env = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!shell_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		tmp = ft_substr(envp[i], 0, j);
		add_envvar(shell_env, tmp, &(envp[i][j + 1]));
		free(tmp);
		i++;
	}
	shell_env->envp = arrstr_copy(envp);
	return (shell_env);
}

void	append_envp(t_env *shell_env, char *name, char *content)
{
	add_envvar(shell_env, name, content);
	free_ptr_str(shell_env->envp);
	shell_env->envp = init_envv(shell_env);
	if (!shell_env->envp)
	{
		write(2, "minishell: memory allocation error occured", 42);
		exit(255);
	}
}

void	add_path(t_env *shell_env, char *path)
{
	char	*old_path;
	char	*new_path;

	old_path = get_variable_value("PATH", shell_env);
	if (ft_strnstr(old_path, path, ft_strlen(path)))
		return ;
	new_path = ft_strjoin_free(old_path, ":");
	new_path = ft_strjoin_free(new_path, path);
	append_envp(shell_env, "PATH", new_path);
	free(new_path);
}
