
#include "parsing.h"

static char	*get_envvar(const char *txt, t_env *root)
{
	char		*new_txt;
	char		*tmp_1;
	char		*tmp_2;
	uint32_t	i;

	i = 0;
	while (txt[i] && txt[i] != '*')
		i++;
	if (!ft_isalnum(txt[i + 1]) && txt[i + 1] != '_')
		return (ft_strdup(txt));
	new_txt = ft_substr(txt, 0, i);
	if (!new_txt)
		return (error_general(new_txt)); // ?? protect
	tmp_1 = ft_substr(txt, i + 1, del_pos(&txt[i + 1]));
	if (!tmp_1)
		return (NULL); // ?? protect
	tmp_2 = find_var(root, tmp_1);
	if (!tmp_2)
		return (NULL); // ?? protect
	free(tmp_1);
	tmp_1 = new_txt;
	new_txt = ft_strjoin(tmp_1, tmp_2); // protect
	free(tmp_1);
	free(tmp_2);
	tmp_1 = new_txt;
	new_txt = ft_strjoin(tmp_1, &txt[i + del_pos(&txt[i + 1]) + 1]);
	free(tmp_1);
	return (new_txt);
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
