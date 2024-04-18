/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:30:03 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:30:03 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../../libft/libft.h"
# include <stdbool.h>

typedef struct s_tree
{
	char			letter;
	bool			exists;
	char			*name;
	struct s_tree	*child;
	struct s_tree	*next;
}					t_tree;

t_tree		*init_tree(const char **name);
void		find_wildcard(char	***matches, char *letters, t_tree *shell_env);
void		add_branch(t_tree *shell_env, const char *name, const char *content);
void		terminate_tree(t_tree *tree);

#endif
