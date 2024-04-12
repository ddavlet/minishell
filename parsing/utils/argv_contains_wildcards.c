#include "../parsing.h"

int contains_wildcards(const char *literal)
{
    const char  *wildcard;

	wildcard = ft_strchr(literal, '*');
	while (wildcard && is_between_quotes(wildcard - literal, literal))
		wildcard = ft_strchr(wildcard + 1, '*');
    if (wildcard)
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
