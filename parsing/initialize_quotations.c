#include "parsing.h"

const char  **get_argv_merged(const char **argv)
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
		if (contains_quotations(argv[i]))
			new[i] = merge_quotations_(argv[i]);
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

void    initialize_quotations(t_cmd2 *cmds, t_env *shell_env)
{
	const char	**argv_new;
	t_cmd2		*cmd;

	cmd = cmds;
	if (!cmds || !cmd->execution || !cmd->execution->argv)
		terminate_parsing(NULL, shell_env, cmds, "missing cmds");
	while (cmd)
	{
		if (argv_contains_quotations(cmd->execution->argv))
		{
			argv_new = get_argv_merged(cmd->execution->argv);
			if (!argv_new)
				terminate_parsing(NULL, shell_env, cmds,
					"minishell: failed to initialize variables");
			if (replace_argv(cmd, argv_new) == -1)
				terminate_parsing(NULL, shell_env, cmds,
					"minishell: failed to initialize variables");
		}
        cmd = cmd->next;
	}
}