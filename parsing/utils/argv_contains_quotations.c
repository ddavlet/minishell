#include "../parsing.h"

int contains_quotations(const char *literal)
{
    char    *quotes;

    quotes = ft_strchr(literal, '\'');
    if (quotes && literal - quotes == 0)
        return (1);
    else if (quotes && *(quotes - 1) != '\\')
        return (1);
    quotes = ft_strchr(literal, '\"');
    if (quotes && literal - quotes == 0)
        return (1);
    else if (quotes && *(quotes - 1) != '\\')
        return (1);
    return (0);
}

int	argv_contains_quotations(const char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
        if (contains_quotations(argv[i]))
            return (1);
		i++;
	}
	return (0);
}
