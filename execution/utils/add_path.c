#include "../execution.h"

t_path	*add_path(t_path **path, t_path *next)
{
    t_path  *path_new;

	if (!next)
		return (NULL);
	if (ft_strncmp(next->name, ".", 2) == 0)
		path_new = initialize_path(getcwd(NULL, 0));
	else if (ft_strncmp(next->name, "~", 2) == 0)
		path_new = initialize_path(getenv("HOME"));
	else if (ft_strncmp(next->name, "..", 3) == 0)
		path_new = remove_last_in(initialize_path(getcwd(NULL, 0)));
	else if (*path == NULL)
        path_new = next;
    
    while (path_new->child_dir != NULL)
        path_new = path_new->child_dir;
    path_new->child_dir = path_new;

    return (*path);
}
