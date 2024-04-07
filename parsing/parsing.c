#include "parsing.h"

uint32_t	count_commands(char **token)
{
	uint32_t	count;
	uint32_t	cnt_scope;

	count = 1;
	cnt_scope = 0;
	while (*token)
	{
		if (parenth_type(*token) == 1)
			cnt_scope++;
		else if (parenth_type(*token) == 2)
			cnt_scope--;
		else if (oper_type(*token) && cnt_scope == 0)
			count++;
		token++;
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
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;

	i = 0;
	j = 0;
	k = 1;
	commands = (t_cmd **)ft_calloc(count_commands(tokens) + 1, sizeof(t_cmd *));
	if (!commands)
		return (error_general(commands, "commands structure")); // catch it!
	while (tokens[j]) // incrase efficiency
	{
		if (parenth_type(tokens[k])
			|| parenth_type(tokens[k - 1]))
			commands[i] = set_scope(tokens, &k);
		j = find_next_cmd(tokens, k); // protect prom segfault
		if (commands[i])
			i++;
		if (parenth_type(tokens[k])
			|| parenth_type(tokens[k - 1]))
				continue ;
		commands[i] = init_cmd(tokens, k, j);
		if (!commands[i++])
			return (terminate_commands(commands));
		k = j + 1;
		if (!tokens[k] || !tokens[k - 1] || !tokens[k + 1])
			break ;
	}
	return (commands);
}

t_cmd	**parse_text(const char *token, t_env *root)
{
	t_cmd		**commands;
	char		**tokens;
	uint32_t	i;

	tokens = pars_split(token);
	// debug_print_array_strings(tokens);
	tokens = merge_quotations(tokens);
	if (!tokens)
		return (NULL); // ?? catch it, mein Freund
	// get_variable(tokens, root);
	get_special_cases(tokens);
	tokens = get_wildcard(tokens, root); // get wildcards after treating $ sign
	if (!tokens)
		return (NULL);
	add_escape(tokens);
	trim_quotes(tokens);
	tokens = pars_merge(tokens);
	tokens = parse_delspace(tokens);
	// debug_print_array_strings(tokens);
	if (!check_tokens(tokens))
		return (terminate_ptr_str(tokens)); // ?? catch it, mein Freund
	commands = init_commands(tokens);
	i = 0;
	while (commands && commands[i])
		commands[i++]->env = root; // change this
	terminate_ptr_str(tokens);
	return (commands);
}
