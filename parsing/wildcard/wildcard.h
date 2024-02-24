#include "../parsing.h"

typedef struct s_tree
{
	char			letter;
	bool			exists;
	char			*name;
	struct s_tree	*child;
	struct s_tree	*next;
}					t_tree;

