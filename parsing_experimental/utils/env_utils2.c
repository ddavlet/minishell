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

const char	*get_variable_name(const char *literal)
{
	const char	*dollar_sign;
	size_t		len;

	dollar_sign = find_variable(literal);
	if (!dollar_sign)
		return (NULL);
	len = 0;
	while (*dollar_sign && ft_isalpha(*(++dollar_sign)))
		len++;
	return (ft_substr(literal, dollar_sign - literal + 1, len));
}

char	*get_envvar(const char *literal, t_env *shell_env)
{
	char		*new;
	const char	*dollar_sign;
	const char		*tmp_1;
	char		*tmp_2;

	dollar_sign = find_variable(literal);
	if (!dollar_sign)
		return (NULL);
	if (!ft_isalpha(*(dollar_sign + 1)))
		return (ft_strdup(literal));
	new = ft_substr(literal, 0, dollar_sign - literal);
	if (!new)
		return (error_general(new, "get_envvar"));
	tmp_1 = get_variable_name(literal);
	if (!tmp_1)
		return (NULL);
	tmp_2 = get_shell_variable(shell_env, tmp_1);
	free((void *)tmp_1);
	if (!tmp_2)
		return (error_general(new, "get_envvar"));
	new = ft_strjoin_free(new, tmp_2);
	free(tmp_2);
	return (ft_strjoin_free(new, dollar_sign + 2));
}

char	*get_shell_variable(t_env *shell_env, const char *search)
{
	t_env	*child;

	if (!search)
		return (NULL);
	child = shell_env->child;
	while (child)
	{
		if (child->letter == *search && *(search + 1)) // need to be checked~
		{
			child = child->child;
			search++;
		}
		else if (child->letter == *search && !*(search + 1))
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
