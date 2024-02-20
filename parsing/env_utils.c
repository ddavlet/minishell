#include "parsing.h"

t_env	*init_env(const char **envp)
{
	t_env		*root;
	uint32_t	i;
	uint32_t	j;
	char		*tmp;

	root = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!root)
		return (error_env_init());
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		tmp = ft_substr(envp[i], 0, j);
		add_envvar(root, tmp, &(envp[i][j + 1]));
		free(tmp);
		i++;
	}
	env_copy(root, envp);
	return (root);
}

void	add_envnode(t_env **list_p, char c, const char *content)
{
	t_env	*last;
	t_env	*new_node;

	last = *list_p;
	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return ; //dela with this return
	if (content)
	{
		new_node->content = ft_strdup(content);
		new_node->exists = true;
	}
	new_node->letter = c;
	if (!last)
		*list_p = new_node;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

void	add_envvar(t_env *root,const char *envvar, const char *content)
{
	t_env	**child_p;

	child_p = &root->child;
	while (*envvar)
	{
		while ((*child_p) && *envvar != (*child_p)->letter)
			child_p = &((*child_p)->next);
		if (!(*child_p) && *(envvar + 1))
		{
			add_envnode(child_p, *envvar, NULL);
			child_p = &((*child_p)->child);
		}
		else if (!(*child_p) && !*(envvar + 1))
			add_envnode(child_p, *envvar, content);
		else if (*(envvar + 1))
			child_p = &((*child_p)->child);
		else if (!*(envvar + 1))
			(*child_p)->content = ft_strdup(content);
		envvar++;
	}
}

char	*get_envvar(const char *txt, t_env *root)
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
		return (NULL); // ?? protect
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

void	env_copy(t_env *root, const char **envp)
{
	char		**copy_envp;
	uint32_t	len;

	while (envp[i])
		i++;
	copy_envp = (char **)ft_calloc(sizeof (char *), i + 1);
	i = 0;
	while (envp[i])
		copy_envp = ft_strdup(envp[i++]);
	root->content = copy_envp;
}
