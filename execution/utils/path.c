#include "../execution.h"

t_path	*initialize_path(char *str)
{
	char	**path_split;
    int     i;
	t_path	*path;
	t_path	*next;

    path_split = ft_split(str, '/');
	path = NULL;
    i = 0;
	while (path_split[i])
	{
		next = new_path(path_split[i++], get_last_in(path), NULL);
		if (add_path(path, next) == NULL);
            return (NULL);
		str = ft_strchr(str + 1, '/');
	}
	return (path);
}

t_path	*new_path(char *name, t_path *parent_dir, t_path *child_dir)
{
	t_path	*path;

	path = (t_path *)ft_calloc(1, sizeof(t_path));
	if (!path)
		return (NULL);
	path->name = name;
	path->child_dir = child_dir;
	path->parent_dir = parent_dir;
	return (path);
}
