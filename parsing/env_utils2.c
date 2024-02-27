#include "parsing.h"

char	*strjoin_free(char *s1, char const *s2)
{
	ssize_t	i;
	ssize_t	j;
	char	*ptr;

	i = -1;
	j = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc((j + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (*s2)
		ptr[i++] = *s2++;
	free(s1);
	ptr[i] = '\0';
	return (ptr);
}

int	var_exists(char *arg)
{
	while (*arg && *arg != '=')
		arg++;
	if (!*arg)
		return (0);
	else
		return (1);
}

char	*get_envvar(const char *txt, t_env *root)
{
	char		*new_txt;
	char		*tmp_1;
	char		*tmp_2;
	uint32_t	i;

	i = 0;
	while (txt[i] && txt[i] != '$')
		i++;
	if (!txt[i] || !txt[i + 1] || (!ft_isalnum(txt[i + 1]) && txt[i + 1] != '_'))
		return (ft_strdup(txt));
	new_txt = ft_substr(txt, 0, i);
	if (!new_txt)
		return (error_general(new_txt, "get_envvar")); // ?? protect
	tmp_1 = ft_substr(txt, i + 1, del_pos(&txt[i + 1]));
	if (!tmp_1)
		return (NULL); // ?? protect
	tmp_2 = find_var(root, tmp_1);
	if (!tmp_2)
		return (NULL); // ?? protect
	tmp_1 = new_txt;
	new_txt = strjoin_free(tmp_1, tmp_2); // protect
	free(tmp_2);
	tmp_1 = new_txt;
	new_txt = strjoin_free(tmp_1, &txt[i + del_pos(&txt[i + 1]) + 1]);
	return (new_txt);
}

void	get_variable(char **tokens, t_env *root)
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
				tokens[i] = get_envvar(tmp, root);
				free(tmp);
				j++;
			}
		}
		i++;
	}

}

char	*find_var(t_env	*root, char *search)
{
	t_env	*child;

	child = root->child;
	if (!search)
		return (NULL);
	while (child)
	{
		if (child->letter == *search && *(search + 1)) // need to be checked~
		{
			child = child->child;
			search++;
		}
		else if (child->letter == *search && !*(search + 1))
		{
			if (child->exists == true)
				return (ft_strdup(child->content));
			else
				return (ft_strdup(""));
		}
		else
			child = child->next;
	}
	free (search);
	return (ft_strdup(""));
}
