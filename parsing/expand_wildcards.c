#include "parsing.h"

void	expand_wildcards(t_cmd2 *cmds, t_env *shell_env)
{
	const char  **argv_new;
	t_cmd2		*cmd;

	cmd = cmds;
	if (!cmds)
        terminate_parsing(NULL, shell_env, cmds, "missing cmds");
    while (cmd)
	{
		if (argv_contains_wildcards(cmd->execution->argv))
		{
			argv_new = (const char **)get_wildcard((char **)cmd->execution->argv, shell_env);
			if (!argv_new)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
			if (replace_argv(cmd, argv_new) == -1)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
		}
		cmd = cmd->next;
	}
}
