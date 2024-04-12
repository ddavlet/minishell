#include "parsing.h"

void    process_wildcards(const char *literal, const char **argv_new, t_env *shell_env)
{
    
}

const char	**get_wildcards_argv(const char **argv, t_env *shell_env)
{
	const char	**new;
	int	i;

	i = get_wildcard_argv_len(argv);
	new = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		if (contains_wildcards(argv[i]))
			process_wildcards(argv[i], new, shell_env);
		else
			new[i] = ft_strdup(argv[i]);
		if (!new[i])
		{
			free_argv(new);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

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
			argv_new = get_wildcards_argv(cmd->execution->argv, shell_env);
			if (!argv_new)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
			if (replace_argv(cmd, argv_new) == -1)
				terminate_parsing(NULL, shell_env, cmds, "minishell: failed to initialize variables");
		}
		cmd = cmd->next;
	}
}
