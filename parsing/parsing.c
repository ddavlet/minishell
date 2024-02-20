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

void	get_variable(char **tokens, t_env *root)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		if (!(tokens[i][0] == '\''))
		{
			while (ft_strchr(tokens[i], '*'))
			{
				tmp = tokens[i];
				tokens[i] = get_envvar(tmp, root);
				free(tmp);
			}
		}
		i++;
	}

}

t_cmd	**parse_text(const char *txt, t_env *root)
{
	t_cmd	**commands;
	char	**tokens;
	int		i;  //assume that number of command are less then int

	i = 0;
	tokens = pars_split(txt);
	tokens = merge_quotations(tokens);
	if (!tokens)
		return (NULL); // ?? catch it, mein Freund
	get_variable(tokens, root);
	commands = (t_cmd **)ft_calloc(count_commands(tokens), sizeof(t_cmd *));
	// while (i < count_commands(tokens))
	// {
	// 	commands = commands[i]
	// }
	debug_print_array_strings(tokens);
	terminate_tokens(tokens);
	(void)commands;
	return (NULL);
}

// test purmose main:

