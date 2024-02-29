#include "parsing.h"

static t_tree	*read_directory(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_tree			*root;

	root = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	dir = opendir("./wildcard/test");
	if (!dir)
	{
		perror("wildcard parsing error");
		return (NULL); // catch it!
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == 8) // ??
			add_branch(root, entry->d_name, entry->d_name);
		entry = readdir(dir);
	}
	return (root);
}

char	**get_wildcard(char **tokens)
{
	ssize_t	i;
	ssize_t	j;
	char	**str;
	t_tree	*root;

	i = 0;
	str = (char **)ft_calloc(sizeof(char *), 1);
	root = read_directory();
	if (!str || !root)
		return (NULL); // free first and catch this error
	while (tokens[++i])
	{
		j = -1;
		while (!ft_isquotation(tokens[i][0]) && tokens[i][++j]) // and no quotatin
		{
			if (tokens[i][j] == 42)
			{
				find_wildcard(&str, tokens[i], root);
				tokens = inject_string(tokens, str, i); // split an deject from here
				break;
			}
		}
	}
	return (tokens);
}
