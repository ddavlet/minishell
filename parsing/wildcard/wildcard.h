#ifndef WILDCARD_H
# define WILDCARD_H

# include "../parsing.h"

typedef struct s_tree
{
	char			letter;
	bool			exists;
	char			*name;
	struct s_tree	*child;
	struct s_tree	*next;
}					t_tree;

t_tree	*init_tree(const char **envp);
void	router(char	***matches, char *letters, t_tree *root);


#endif
