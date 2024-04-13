#include "parsing.h"

int	get_total_length(char ***expanded)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (expanded[i])
	{
		j = 0;
		while (expanded[i][j])
		{
			len++;
			j++;
		}
		i++;
	}
	return (len);
}

char	**get_wildcards_argv(char ***argv_expanded, int len)
{
	int		i;
	int		j;
	char	**argv_new;

	if (!argv_expanded)
		return (NULL);
	argv_new = (char **)ft_calloc(len + 1, sizeof(char **));
	if (!argv_new)
		return (NULL);
	i = -1;
	while (argv_expanded[++i])
	{
		j = -1;
		while (argv_expanded[i][++j])
		{
			argv_new[i + j] = ft_strdup(argv_expanded[i][j]);
			if (!argv_new[i][j])
			{
				free_argv((const char **)argv_new);
				return (NULL);
			}
		}
	}
	free_array_3d(argv_expanded);
	return (argv_new);
}

void	expand_wildcards(t_cmd2 *cmds, t_env *shell_env)
{
	char		***expanded;
	const char	**argv_new;
	int			new_len;
	t_cmd2		*cmd;

	cmd = cmds;
	if (!cmds)
		terminate_parsing(NULL, shell_env, cmds, "missing cmds");
	while (cmd)
	{
		if (argv_contains_wildcards(cmd->execution->argv))
		{
			expanded = get_wildcard(cmd->execution->argv, shell_env);
			if (!expanded)
				terminate_parsing(NULL, shell_env, cmds,
					"minishell: failed to initialize variables");
			new_len = get_total_length(expanded);
			argv_new = (const char **)get_wildcards_argv(expanded, new_len);
			if (replace_argv(cmd, argv_new) == -1)
				terminate_parsing(NULL, shell_env, cmds,
					"minishell: failed to initialize variables");
		}
		cmd = cmd->next;
	}
}
