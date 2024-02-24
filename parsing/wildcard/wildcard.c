#include "wildcard.h"

void	parse_wildcard(char *txt)
{

}

char	**f_2(char	**matches, char *letters, t_tree *root)
{
	t_tree	*child;

	child = root;
	while (child)
	{
		if (child->letter == letters[1])
			router(matches, letters, child->child);
		child = child->next;
	}
}
char	**f_1(char	**matches, char *letters, t_tree *root)
{

}

void	f_3(char	**matches, t_tree *root)
{
	t_tree	*child;

	child = root;
	if (!child)
		return ;
	while (child)
	{
		f_3(matches, child->child);
		if (child->exists)
			append_arr_str(matches, ft_strdup(child->name));
		child = child->next;
	}
}

char	**router(char	**matches, char *letters, t_tree *root)
{
	if (letters[1] == 42)
	{
		if (!letters[1])
			return (f_3(matches, root)); // ??
		else
			f_2(matches, letters, root);
	}
	else
		f_1(matches, letters, root);
}
