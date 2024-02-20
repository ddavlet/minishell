#include "parsing.h"

t_oper	oper_type(char *txt)
{
	if (ft_strncmp(txt, "|", 2))
		return (PIPE);
	if (ft_strncmp(txt, "||", 3))
		return (OR);
	if (ft_strncmp(txt, "&&", 3))
		return (AND);
	else
		return (RUN);
}
