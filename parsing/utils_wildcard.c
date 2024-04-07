#include "parsing.h"

static t_tree	*read_directory(t_env	*env)
{
	DIR				*dir;
	struct dirent	*entry;
	t_tree			*tree;
	char			*tmp;

	tmp = get_shell_variable(env, "PWD"); // change to what we need
	dir = opendir(tmp);
	free(tmp);
	if (!dir)
	{
		perror("wildcard parsing error");
		return (NULL); // catch it!
	}
	tree = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == 8) // ??
			add_branch(tree, entry->d_name, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (tree);
}

char	**get_wildcard(char **tokens, t_env *env)
{
	ssize_t	i;
	ssize_t	j;
	char	**str;
	t_tree	*tree;

	i = 0;
	str = (char **)ft_calloc(sizeof(char *), 1);
	tree = read_directory(env);
	if (!str || !tree)
	{
		terminate_ptr_str(tokens);
		return (ft_free_ptr(str, tree)); // free first and catch this error
	}
	while (tokens[++i])
	{
		j = -1;
		while (!ft_isquotation(tokens[i][0]) && tokens[i][++j]) // and no quotatin
		{
			if (tokens[i][j] == 42)
			{
				find_wildcard(&str, tokens[i], tree);
				tokens = inject_string(tokens, str, i); // split an deject from here
				terminate_ptr_str(str);
				break;
			}
		}
	}
	terminate_tree(tree);
	return (tokens);
}
