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
void		find_wildcard(char	***matches, char *letters, t_tree *root);
void		add_branch(t_tree *root, const char *name, const char *content);
void		terminate_tree(t_tree *tree);

#endif
