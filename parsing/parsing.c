#include "parsing.h"

int	count_commands(char **txt) //here max value of commands is limited to int. Need protection?
{
	int	count;

	count = 1;
	while (*txt)
	{
		if (*txt[0] == '|')
			count++;
		else if (*txt[0] == '&')
			count++;
		txt++;
	}
	return (count);
}

t_cmd	*init_cmd(char **tokens, int i)
{
	t_cmd	*cmd;
	t_redir	**redir;
	ssize_t	j;

	j = 0;
	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (error_general(cmd)); // protection
	redir = (t_redir **)ft_calloc(sizeof(redir), 1);
	if (!redir)
		return (error_general(redir)); // protect + free previous malloc
	while (tokens[j] && !ft_isexeption(tokens[j][0]))
	{
		if (ft_isrediraction(tokens[j]))
			append_redirnode(redir, ft_isrediraction(tokens[j]), tokens[j + 1]);
		else
			cmd->com = tokens[i];
	}
	(void)i;
	return (NULL);
}

t_cmd	**init_commands(char **tokens)
{
	t_cmd	**commands;
	int				i;  //assume that number of command are less then int

	i = 0;
	commands = (t_cmd **)ft_calloc(count_commands(tokens) + 1, sizeof(t_cmd *));
	if (!commands)
		return (error_general(commands)); // catch it!
	while (i < count_commands(tokens))
	{
		commands[i] = init_cmd(tokens, i + 1);
	}
	return (NULL);
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
	commands = init_commands(tokens);
	debug_print_array_strings(tokens);
	terminate_ptr_str(tokens);
	(void)commands;
	return (NULL);
}

// test purmose main:

