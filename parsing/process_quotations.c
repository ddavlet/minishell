#include "parsing.h"

const char	**process_quotations_argv(const char **argv)
{
	const char	**new;
	int			i;

	new = (const char **)ft_calloc(ft_arr_len((char **)argv) + 1,
			sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		if (contains_quotations(argv[i]))
			new[i] = merge_quotations(argv[i]);
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

void	process_quotations(t_cmd2 *cmds, t_env *shell_env)
{
	const char **argv_new;
	t_cmd2 *cmd;

	cmd = cmds;
	if (!cmds || !cmd->execution || !cmd->execution->argv || !shell_env)
		terminate_parsing(NULL, shell_env, cmds,
			"minishell: parser failed to process quotations");
	while (cmd)
	{
		if (argv_contains_quotations(cmd->execution->argv))
		{
			argv_new = process_quotations_argv(cmd->execution->argv);
			if (!argv_new)
				terminate_parsing(NULL, shell_env, cmds,
					"minishell: parser failed to process quotations");
			if (replace_argv(cmd, argv_new) == -1)
				terminate_parsing(NULL, shell_env, cmds,
					"minishell: parser failed to process quotations");
		}
		cmd = cmd->next;
	}
}