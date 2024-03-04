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

int	*remove_scope(int *scope)
{
	int32_t	i;
	int		*new_scope;

	i = 0;
	while (scope[i])
		i++;
	new_scope = (int *)ft_calloc(sizeof(int), i - 1);
	if (!new_scope)
	{
		free(scope);
		return (NULL);
	}
	i = -1;
	while (scope[++i + 1])
		new_scope[i] = scope[i + 1];
	free(scope);
	return (new_scope);
}

int	*add_scope(int *scope)
{
	int32_t	i;
	int		*new_scope;

	i = 0;
	while (scope[i])
		i++;
	new_scope = (int *)ft_calloc(sizeof(int), i + 2);
	if (!new_scope)
	{
		free(scope);
		return (NULL);
	}
	i = scope[0];
	new_scope[0] = id_gen(i);
	i = -1;
	while (scope[++i])
		new_scope[i + 1] = scope[i];
	free(scope);
	return (new_scope);
}

int	*set_priority(char **tokens, ssize_t prev, ssize_t next, int *scope)
{
	int		count;
	ssize_t	tmp;

	count = 0;
	tmp = prev;
	if (prev == next)
		return (0);
	scope = ft_intarrdup(scope);
	while (ft_isparenthesis(tokens[prev++]) == 1)
		scope = add_scope(scope);
	if (tmp-- > 2)
		while (ft_isparenthesis(tokens[--tmp]) == 2)
			scope = remove_scope(scope);
	while (ft_isparenthesis(tokens[next--]))
		;
	while (prev < next)
	{
		if (ft_isparenthesis(tokens[prev]) == 1)
			return (NULL);
		else if (ft_isparenthesis(tokens[prev]) == 2)
			return (NULL);
		prev++;
	}
	return (scope);
}

t_cmd	*init_cmd(char **tokens, ssize_t prev, ssize_t next, int **scope)
{
	t_cmd	*cmd;

	if (prev == 1)
		prev--;
	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (error_general(cmd, "cmd")); // protection
	cmd->redirs = init_redir(tokens, prev, next);
	cmd->operat = oper_type(tokens[next]);
	cmd->context_stack = set_priority(tokens, prev, next, *scope);
	*scope = cmd->context_stack;
	if (!cmd->context_stack)
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
	int				*scope;

	i = 0;
	j = 0;
	commands = (t_cmd **)ft_calloc(count_commands(tokens) + 1, sizeof(t_cmd *));
	scope = (int *)ft_calloc(sizeof(int), 2);
	scope[0] = 1;
	if (!commands)
		return (error_general(commands, "commands structure")); // catch it!
	while (i < count_commands(tokens)) // incrase efficiency
	{
		k = j + 1;
		j = find_next_cmd(tokens, k); // protect prom segfault
		commands[i] = init_cmd(tokens, k, j, &scope);
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
	// if (commands)
	// 	change_priority(commands);
	terminate_ptr_str(tokens);
	return (commands);
}
