#include "../parsing.h"

static t_tree	*read_directory(t_env	*env)
{
	DIR				*dir;
	struct dirent	*entry;
	t_tree			*tree;
	char			*tmp;

	tmp = get_variable_value("PWD", env); // change to what we need
	dir = opendir(tmp);
	free(tmp);
	if (!dir)
	{
		ft_putendl_fd("wildcard parsing error", STDERR_FILENO);
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

char	**get_wildcard(char **argv, t_env *env)
{
	ssize_t	i;
	char	**arguments;
	t_tree	*tree;

	i = 0;
	arguments = (char **)ft_calloc(sizeof(char *), 1);
	tree = read_directory(env);
	if (!arguments || !tree)
	{
		free_ptr_str(argv);
		return (ft_free_ptr(arguments, tree));
	}
	while (argv[++i])
	{
        if (contains_wildcards(argv[i]))
		{
            find_wildcard(&arguments, argv[i], tree);
            argv = inject_string(argv, arguments, i);
            free_ptr_str(arguments);
		}
	}
	terminate_tree(tree);
	return (argv);
}
