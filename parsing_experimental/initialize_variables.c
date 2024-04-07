#include "parsing2.h"

const char  *replace_variables(const char *literal, t_env *shell_env)
{
    char    *old;
    char    *new;

    old = literal;
    new = literal;
    while (find_variable(new))
    {
        if (is_special_case(old))
            new = get_case(old, shell_env);
        else 
            new = get_envvar(old, shell_env);
        free(old);
        if (!new)
            return (NULL);
        old = new;
    }
    return ((const char *)new);
}

const char	**get_argv_variables(const char **argv, t_env *shell_env)
{
	const char	**new;
	int	i;

	i = ft_arr_len(argv);
	new = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		if (has_variables(argv[i]))
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

void	initialize_variables(t_cmd2 *cmds, t_env *shell_env)
{
	const char  **argv_new;
	t_cmd2		*cmd;

	cmd = cmds;
	cmd_check(cmd);
	while (cmd)
	{
		if (argv_contains_variables(cmd->execution->argv))
		{
			argv_new = get_argv_variables(cmd->execution->argv, shell_env);
			if (!argv_new)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
			if (replace_argv(cmd, argv_new) == -1)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
		}
		cmd = cmd->next;
	}
}
