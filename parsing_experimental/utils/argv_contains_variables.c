#include "../parsing2.h"

int	argv_contains_variables(const char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (find_variable(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	edge_case(const char *literal, const char *dollar_sign)
{
	if (is_between_char(dollar_sign - literal, literal, '\''))
		return (1);
	if (!ft_isalpha(*(dollar_sign + 1)) && *(dollar_sign + 1) != '?')
		return (1);
	if ((literal - dollar_sign != 0) && *(dollar_sign - 1) == '\\')
		return (1);
	return (0);
}

const char	*find_variable(const char *literal)
{
	const char *sign;

	sign = ft_strchr(literal, '$');
	while (sign && edge_case(literal, sign))
		sign = ft_strchr(sign + 1, '$');
	return (sign);
}