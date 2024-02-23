#include "parsing.h"

int	count_commands(char **txt) //here max value of commands is limited to int. Need protection?
{
	int	count;

	count = 1;
	while (*txt)
	{
		if (oper_type(*txt))
			count++;
		txt++;
	}
	return (count);
}

t_cmd	*init_cmd(char **tokens, ssize_t prev, ssize_t next)
{
	t_cmd	*cmd;

	if (prev == next)
		return (error_near_tocken(tokens[prev])); // catch it! error already printed
	else if (prev == 1)
		prev--;
	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (error_general(cmd, "cmd")); // protection
	cmd->redirs = init_redir(tokens, prev, next);
	cmd->operat = oper_type(tokens[next]);
	cmd->argv = create_argv(tokens, prev, next + 1);
	if (cmd->argv)
	{
		if (cmd->argv[0])
			cmd->com = ft_strdup(cmd->argv[0]); // protect
	}
	else
		return (terminate_cmd(cmd));
	return (cmd);
}

t_cmd	**init_commands(char **tokens)
{
	t_cmd	**commands;
	int				i; //assume that number of command are less then int
	ssize_t			j; // tell when is the next command
	ssize_t			k; // tell when is the prev command

	i = 0;
	j = 0;
	commands = (t_cmd **)ft_calloc(count_commands(tokens) + 1, sizeof(t_cmd *));
	if (!commands)
		return (error_general(commands, "commands structure")); // catch it!
	while (i < count_commands(tokens)) // incrase efficiency
	{
		k = j + 1;
		j = find_next_cmd(tokens, k); // protect prom segfault
		commands[i] = init_cmd(tokens, k, j);
		if (!commands[i++])
			return (terminate_commands(commands));
	}
	return (commands);
}

t_cmd	**parse_text(const char *txt, t_env *root)
{
	t_cmd	**commands;
	char	**tokens;

	tokens = pars_split(txt);
	tokens = merge_quotations(tokens);
	if (!tokens)
		return (NULL); // ?? catch it, mein Freund
	get_variable(tokens, root);
	add_escape(tokens, "\\");
	trim_quotes(tokens);
	tokens = pars_merge(tokens);
	tokens = parse_delspace(tokens);
	debug_print_array_strings(tokens);
	if (!check_tokens(tokens))
	{
		terminate_ptr_str(tokens);
		return (NULL);
	}
	commands = init_commands(tokens);
	terminate_ptr_str(tokens);
	return (commands);
}

// test purmose main:

