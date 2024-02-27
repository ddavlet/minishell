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

t_cmd	*init_cmd(char **tokens, ssize_t prev, ssize_t next)
{
	t_cmd	*cmd;

	// if (prev == next)
	// 	return (error_near_tocken(tokens[prev])); // catch it! error already printed
	// else if (prev == 1)
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

int	spec_case(char c)
{
	if (c == '?')
		return (1);
	else if (c == '$')
		return (2);
	else
		return (0);
}

char	*case_handler(int key)
{
	if (key == 1)
		return (ft_strdup("exit_code"));
	if (key == 2)
		return (ft_itoa(getpid()));
	else
		return (NULL);
}

static char *get_case(char *token)
{
	char		*new_txt;
	char		*tmp_1;
	char		*tmp_2;
	uint32_t	i;

	i = 0;
	while (token[i] && token[i] != '$')
		i++;
	if (!token[i] || (!token[i + 1] && !spec_case(token[i + 1])))
		return (ft_strdup(token));
	new_txt = ft_substr(token, 0, i);
	if (!new_txt)
		return (error_general(new_txt, "get_envvar")); // ?? protect
	tmp_2 = case_handler(spec_case(token[i + 1])); // exit code goes here!!
	if (!tmp_2)
		return (NULL); // ?? protect
	tmp_1 = new_txt;
	new_txt = strjoin_free(tmp_1, tmp_2); // protect
	free(tmp_2);
	tmp_1 = new_txt;
	new_txt = strjoin_free(tmp_1, &token[i + 2]);
	return (new_txt);
}

void	get_special_cases(char **tokens)
{
	ssize_t		i;
	uint32_t	j;
	char		*tmp;

	i = 0;
	while (tokens[i])
	{
		if (!(tokens[i][0] == '\''))
		{
			j = 0;
			while (ft_strchr(tokens[i], '$') && j < ft_strlen(tokens[i])) // a bit inefficient
			{
				tmp = tokens[i];
				tokens[i] = get_case(tmp);
				free(tmp);
				j++;
			}
		}
		i++;
	}
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
	tokens = get_wildcard(tokens); // get wildcards after treating $ sign
	add_escape(tokens, "\\");
	trim_quotes(tokens);
	tokens = pars_merge(tokens);
	tokens = parse_delspace(tokens);
	debug_print_array_strings(tokens);
	if (!check_tokens(tokens))
		return (terminate_ptr_str(tokens)); // ?? catch it, mein Freund
	commands = init_commands(tokens);
	terminate_ptr_str(tokens);
	return (commands);
}

// test purmose main:

