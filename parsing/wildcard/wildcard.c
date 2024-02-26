#include "wildcard.h"


void	f_2(char	**matches, char *letters, t_tree *root)
{
	t_tree	*child;

	child = root;
	if (!child)
		return ;
	while (child)
	{
		if (child->letter == letters[0])
			router(matches, letters, child->child);
		child = child->next;
	}
}
void	f_1(char	**matches, char *letters, t_tree *root)
{
	t_tree	*child;

	child = root;
	if (!child)
		return ;
	while (child)
	{
		if (child->letter == letters[1])
			router(matches, letters, root);
		child = child->next;
	}
	return ;
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

void	router(char	**matches, char *letters, t_tree *root)
{
	if (letters[0] == 42)
	{
		if (!letters[1])
			return (f_3(matches, root)); // any value with the last *
		else if (letters[1] == 42) // this this not exeptable!
			;
		else
			f_2(matches, &letters[1], root); // find char after *
	}
	else if (letters[0])
	{
		if (letters[1] == 42)
			router(matches, &letters[1], root);
		else
			f_1(matches, &letters[1], root);
	}
	else
	{
		if (root->exists)
			append_arr_str(matches, ft_strdup(root->name));
	}
}
