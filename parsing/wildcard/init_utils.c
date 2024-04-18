/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:48 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:29:49 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static void	add_node(t_tree **list_p, char c, const char *content)
{
	t_tree	*last;
	t_tree	*new_node;

	last = *list_p;
	new_node = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	if (!new_node)
		return ; // dela with this return
	new_node->letter = c;
	if (content)
	{
		new_node->exists = true;
		new_node->name = ft_strdup(content);
	}
	if (!last)
		*list_p = new_node;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

void	add_branch(t_tree *shell_env, const char *name, const char *content)
{
	t_tree	**child_p;

	child_p = &shell_env->child;
	while (*name)
	{
		while ((*child_p) && *name != (*child_p)->letter)
			child_p = &((*child_p)->next);
		if (!(*child_p) && *(name + 1))
		{
			add_node(child_p, *name, NULL);
			child_p = &((*child_p)->child);
		}
		else if (!(*child_p) && !*(name + 1))
			add_node(child_p, *name, content);
		else if (*(name + 1))
			child_p = &((*child_p)->child);
		else if (!*(name + 1))
		{
			free((*child_p)->name);
			(*child_p)->name = ft_strdup(content);
			(*child_p)->exists = true;
		}
		name++;
	}
}

t_tree	*init_tree(const char **name)
{
	t_tree		*shell_env;
	uint32_t	i;

	shell_env = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	if (!shell_env)
		return (NULL);
	i = 0;
	if (!name)
		return (shell_env);
	while (name[i])
	{
		add_branch(shell_env, name[i], name[i]);
		i++;
	}
	return (shell_env);
}
