#include "wildcard.h"

static void	router(char	***matches, char *letters, t_tree *root);

static void	f_1(char	***matches, char *letters, t_tree *root)
{
	t_tree	*child;

	child = root;
	if (!child)
		return ;
	while (child)
	{
		if (child->letter == letters[0])
			router(matches, letters, child);
		child = child->next;
	}
	return ;
}

static void	f_2(char	***matches, char *letters, t_tree *root)
{
	t_tree	*child;

	child = root;
	if (!child)
		return ;
	while (child)
	{
		f_2(matches, letters, child->child);
		if (child->letter == letters[1])
			router(matches, &letters[1], child);
		if (letters)
		child = child->next;
	}
}

static void	f_3(char	***matches, t_tree *root)
{
	t_tree	*child;

	child = root;
	if (!child)
		return ;
	while (child)
	{
		f_3(matches, child->child);
		if (child->exists)
			*matches = append_arr_str(*matches, ft_strdup(child->name));
		child = child->next;
	}
}

static void	router(char	***matches, char *letters, t_tree *root)
{
	while (letters[0] == '*' && letters[1] == '*')
		letters++;
	if (letters[0] == 42)
	{
		if (!letters[1])
			return (f_3(matches, root)); // any value with the last *
		else
			f_2(matches, &letters[0], root->child); // find char after *
	}
	else if (letters[1])
	{
		if (letters[1] == 42)
			router(matches, &letters[1], root->child);
		else
			f_1(matches, &letters[1], root->child);
	}
	else
	{
		if (root->exists)
			*matches = append_arr_str(*matches, ft_strdup(root->name));
	}
}

void	find_wildcard(char	***matches, char *letters, t_tree *root)
{
	while (*letters == '*' && *(letters + 1) == '*')
		letters++;
	if (!*(letters + 1) && *letters == '*')
		f_3(matches, root->child);
	else if (*letters == '*')
		f_2(matches, letters, root->child);
	else
		f_1(matches, letters, root->child);
}
