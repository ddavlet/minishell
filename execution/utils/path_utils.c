#include "../execution.h"

char    *get_parent_dir(char *path)
{
    if (get_name(path))
        return (ft_substr(path, 0, path - get_name(path) - 1));
    return (NULL);
}

char	*get_name(char *path)
{
	char	*last;

	last = NULL;
	while (path)
	{
		last = path;
		path = ft_strchr(path, '/');
        if (path)
            path++;
	}
	return (last);
}

int count_paths(const char *string_literal)
{
    int count;
    int i;

    count = 0;
    i = 1;
    while (string_literal[i])
    {
        if (string_literal[i] == '/')
            count++;
        i++;
    }
    if (*string_literal == '/')
        count--;
    return (count);
}

char    *next_pathname_in_literal(const char *string_literal)
{
    if (*string_literal == '/')
        return (ft_strchr(string_literal + 1, '/'));
    if (!ft_strchr(string_literal, '/'))
        return (string_literal);
}

t_path  *get_last_in(t_path *path)
{
    if (!path)
        return (NULL);
    while (path->child_dir != NULL)
        path = path->child_dir;
    return (path);
}