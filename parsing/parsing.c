#include "parsing.h"

uint32_t	count_commands(char **token)
{
	uint32_t	count;

	count = 1;
	while (*token)
	{
		if (oper_type(*token))
			count++;
		token++;
	}
	return (count);
}

void	change_priority(t_cmd **commands)
{
	ssize_t	i;
	int		lvl;
	int		tmp;

	i = -1;
	lvl = 0;
	while (commands[++i])
	{
		if (commands[i]->priority < 0)
		{
			tmp = commands[i]->priority;
			commands[i]->priority = lvl;
			lvl += tmp;
		}
		else if (commands[i]->priority > 0)
		{
			lvl += commands[i]->priority;
			commands[i]->priority = lvl;
		}
		else
			commands[i]->priority = lvl;
	}
}

// int	check_priority(char **tokens, ssize_t prev, ssize_t next)
// {
// 	while (prev < next)
// 	{
// 		if (ft_isparenthesis(tokens[prev]) == 1)
// 		{
// 			if (prev != 0)
// 				return (1);
// 		}
// 		else if (ft_isparenthesis(tokens[prev]) == 2)
// 		{
// 			if (prev != next - 1)
// 				return (1);
// 		}
// 		prev++;
// 	}
// 	return (0);
// }

int	set_priority(char **tokens, ssize_t prev, ssize_t next)
{
	int		count;

	count = 0;
	if (prev == next)
		return (0);
	while (ft_isparenthesis(tokens[prev++]) == 1)
		count++;
	next--;
	while (ft_isparenthesis(tokens[next--]) == 2)
		count--;
	while (prev < next)
	{
		if (ft_isparenthesis(tokens[prev]) == 1)
			return (INT32_MAX);
		else if (ft_isparenthesis(tokens[prev]) == 2)
			return (INT32_MAX);
		prev++;
	}
	return (count);
}

t_cmd	*init_cmd(char **tokens, ssize_t prev, ssize_t next)
{
	t_cmd	*cmd;

	if (prev == 1)
		prev--;
	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (error_general(cmd, "cmd")); // protection
	cmd->redirs = init_redir(tokens, prev, next);
	cmd->operat = oper_type(tokens[next]);
	cmd->priority = set_priority(tokens, prev, next);
	if (cmd->priority == INT32_MAX)
		return (error_syntax(cmd));
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
	t_cmd			**commands;
	uint32_t		i;
	ssize_t			j;
	ssize_t			k;

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

t_cmd	**parse_text(const char *token, t_env *root)
{
	t_cmd	**commands;
	char	**tokens;

	tokens = pars_split(token);
	tokens = merge_quotations(tokens);
	if (!tokens)
		return (NULL); // ?? catch it, mein Freund
	get_variable(tokens, root);
	get_special_cases(tokens);
	tokens = get_wildcard(tokens, root); // get wildcards after treating $ sign
	add_escape(tokens, "\\");
	trim_quotes(tokens);
	tokens = pars_merge(tokens);
	tokens = parse_delspace(tokens);
	// debug_print_array_strings(tokens);
	if (!check_tokens(tokens))
		return (terminate_ptr_str(tokens)); // ?? catch it, mein Freund
	commands = init_commands(tokens);
	if (commands)
		change_priority(commands);
	terminate_ptr_str(tokens);
	return (commands);
}
