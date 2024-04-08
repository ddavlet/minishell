#include "builtin.h"

// "export %s=%s\n", <name>, <value>

int	builtin_export(const char **argv, t_env *root) // recieve code!
{
	uint32_t	i;
	char		*key;
	char		*value;

	i = 1;
	while (argv[i] != NULL)
	{
		key = ft_strcdup(argv[i], '=');
		value = ft_strchr(argv[i], '=');
		if (value == NULL)
		{
			free(key);
			return (1);
		}
		value++;
		append_envp(root, key, value);
		free(key);
		i++;
	}
	return (0);
}
