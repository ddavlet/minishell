#include "parsing.h"

static char **create_argv_repars(char **tokens, ssize_t prev, ssize_t next)
{
	char	**argv;
	ssize_t	i;

	i = prev - 1;
	argv = (char **)ft_calloc(sizeof(char *), 1); // protect
	while (++i < next || (tokens[i] && ft_isexeption(tokens[i])))
	{
		if (oper_type(tokens[i]))
			break ;
		else
			argv = append_arr_str(argv, ft_strdup(tokens[i]));
	}
	return (argv);
}

static t_cmd	*init_cmd(char **tokens, ssize_t prev, ssize_t next)
{
	t_cmd	*cmd;

	if (prev == 1)
		prev--;
	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (error_general(cmd, "cmd")); // protection
	// cmd->redirs = init_redir(tokens, prev, next);
	cmd->operat = oper_type(tokens[next]);
	// cmd->scope_stack = set_priority(tokens, prev, next, *scope);
	// *scope = cmd->scope_stack;
	// if (!cmd->scope_stack)
	// 	return (error_syntax(cmd));
	cmd->argv = create_argv_repars(tokens, prev, next + 1);
	if (cmd->argv)
	{
		if (cmd->argv[0])
			cmd->com = ft_strdup(cmd->argv[0]); // protect
	}
	else
		return (terminate_cmd(cmd));
	return (cmd);
}

t_cmd	**reparse_text(char **argv)
{
	t_cmd			**commands;
	uint32_t		i;
	ssize_t			j;
	ssize_t			k;
	// int				*scope;

	i = 0;
	j = 0;
	commands = (t_cmd **)ft_calloc(count_commands(argv) + 1, sizeof(t_cmd *));
	// scope = (int *)ft_calloc(sizeof(int), 2);
	// scope[0] = 1;
	if (!commands)
		return (error_general(commands, "commands structure")); // catch it!
	while (i < count_commands(argv)) // incrase efficiency
	{
		k = j + 1;
		j = find_next_cmd(argv, k); // protect prom segfault
		commands[i] = init_cmd(argv, k, j); // &scope
		if (!commands[i++])
			return (terminate_commands(commands));
	}
	return (commands);
}
