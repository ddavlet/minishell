#include "../parsing2.h"

int argv_contains_wildcards(const char **argv)
{
	int	i;
	const char *sign;

	i = 0;
	while (argv[i])
	{
		if (find_variable(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

const char  *find_variable(const char *literal)
{
	const char *sign;

	sign = strchr(literal, '$'); 
	while (sign && is_between_char(sign - literal, literal, '\''))
		sign = strchr(sign + 1, '$');
	return (sign);
}