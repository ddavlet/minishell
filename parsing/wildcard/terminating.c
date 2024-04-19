/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminating.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:51 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:29:52 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	terminate_tree(t_tree *tree)
{
	t_tree	*tmp;

	if (!tree)
		return ;
	while (tree)
	{
		terminate_tree(tree->child);
		tmp = tree->next;
		free(tree->name);
		free(tree);
		tree = tmp;
	}
}
