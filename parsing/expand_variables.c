#include "parsing.h"

char	*replace(const char *literal, const char *dollar_sign,
		const char *value)
{
	char		*new;
	const char	*name;

	if (!dollar_sign || !literal || !value)
		return (NULL);
	new = ft_substr(literal, 0, dollar_sign - literal);
	if (!new)
		return (NULL);
	new = ft_strjoin_free(new, value);
	free((char *)value);
	name = get_variable_name(dollar_sign);
	new = ft_strjoin_free(new, dollar_sign + ft_strlen(name) + 1);
	free((char *)name);
	return (new);
}

const char	*replace_variables(const char *literal, t_env *shell_env)
{
	const char	*new;
	const char	*old;
	const char	*value;
	const char	*dollar_sign;

	old = literal;
	new = literal;
	dollar_sign = find_variable(new);
	if (!dollar_sign)
		return (ft_strdup(literal));
	while (dollar_sign)
	{
		value = get_shell_variable(dollar_sign, literal, shell_env);
		new = replace(literal, dollar_sign, value);
		if (ft_strncmp(literal, old, ft_strlen(literal) + 1) != 0)
			free((char *)old);
		if (!new)
			return (NULL);
		old = new;
		dollar_sign = find_variable(new);
	}
	return ((const char *)new);
}

const char	**get_argv_variables(const char **argv, t_env *shell_env)
{
	const char	**new;
	int			i;

	i = ft_arr_len((char **)argv);
	new = (const char **)ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		if (find_variable(argv[i]))
			new[i] = replace_variables(argv[i], shell_env);
		else
			new[i] = ft_strdup(argv[i]);
		if (!new[i])
		{
			free_argv(new);
			return (NULL);
		}
		i++;
	}
	return (new);
}

void	expand_variables(t_cmd2 *cmd, t_env *shell_env)
{
	const char	**argv_new;

	if (!cmd)
		terminate_parsing(NULL, shell_env, cmd, "missing cmds");
	if (argv_contains_variables(cmd->execution->argv))
	{
		argv_new = get_argv_variables(cmd->execution->argv, shell_env);
		if (!argv_new)
			terminate_parsing(NULL, shell_env, cmd,
				"minishell: failed to initialize variables");
		if (replace_argv(cmd, argv_new) == -1)
			terminate_parsing(NULL, shell_env, cmd,
				"minishell: failed to initialize variables");
	}
}
