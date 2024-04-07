#include "parsing2.h"

const char	**get_argv_wildcards(const char **argv, t_env *shell_env)
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

void	initialize_wildcards(t_cmd2 *cmds, t_env *shell_env)
{
	const char  **argv_new;
	t_cmd2		*cmd;

	cmd = cmds;
	cmd_check(cmd);
	while (cmd)
	{
		if (argv_contains_wildcards(cmd->execution->argv))
		{
			argv_new = get_argv_wildcards(cmd->execution->argv, shell_env);
			if (!argv_new)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
			if (replace_argv(cmd, argv_new) == -1)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
		}
		cmd = cmd->next;
	}
}
