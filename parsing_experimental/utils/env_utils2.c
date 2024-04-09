#include "../../parsing/parsing.h"
#include "../parsing2.h"

int	var_exists(char *arg)
{
	while (*arg && *arg != '=')
		arg++;
	if (!*arg)
		return (0);
	else
		return (1);
}

const char	*get_variable_name(const char *dollar_sign)
{
	size_t	len;

	if (!dollar_sign)
		return (NULL);
	dollar_sign++;
	len = 1;
	while (ft_isalnum(*(dollar_sign + len)) || *(dollar_sign + len) == '_')
		len++;
	return (ft_substr(dollar_sign, 0, len));
}

char    *get_last_exit_status(t_env *shell_env)
{
    (void)shell_env;
    return (NULL);
}

char	*get_envvar(const char *dollar_sign, const char *literal,
		t_env *shell_env)
{
	const char	*name;
	char	*value;

	if (!dollar_sign || !literal || !shell_env)
		return (NULL);
	if (*(dollar_sign + 1) == '?')
		value = get_last_exit_status(shell_env);
	else
    {
        name = get_variable_name(dollar_sign);
		value = get_shell_variable(shell_env, name);;
        free((char *)name);
    }
	return (value);
}

char	*get_shell_variable(t_env *shell_env, const char *name)
{
	t_env	*child;

	if (!name)
		return (NULL);
	child = shell_env->child;
	while (child)
	{
		if (child->letter == *name && *(name + 1)) // need to be checked~
		{
			child = child->child;
			name++;
		}
		else if (child->letter == *name && !*(name + 1))
		{
			if (child->exists == true)
				return (ft_strdup(child->content));
			else
				return (ft_strdup(""));
		}
		else
			child = child->next;
	}
	return (ft_strdup(""));
}
