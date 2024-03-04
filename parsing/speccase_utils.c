#include "parsing.h"

static int	spec_case(char c)
{
	if (c == '?')
		return (1);
	else if (c == '$')
		return (2);
	else if (c == '0')
		return (3);
	else if (ft_isdigit(c))
		return (4);
	return (0);
}

static char	*case_handler(int key)
{
	if (key == 1)
		return (ft_strdup("exit_code"));
	if (key == 2)
		return (ft_itoa(getpid()));
	if (key == 3)
		return (ft_strdup("minishell"));
	if (key == 4)
		return (ft_strdup(""));
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
