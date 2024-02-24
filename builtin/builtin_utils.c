#include "builtin.h"
#include "../libft/libft.h"

char	*ft_strcdup(const char *s, int c)
{
	char		*str;
	uint32_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!str)
		return (NULL); // protect
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
