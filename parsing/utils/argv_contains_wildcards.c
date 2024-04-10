#include "../parsing.h"

int contains_wildcards(const char *literal)
{
    if (ft_strchr(literal, '*'))
        return (1);
    return (0);
}

int argv_contains_wildcards(const char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (contains_wildcards(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
