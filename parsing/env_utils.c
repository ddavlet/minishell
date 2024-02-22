#include "parsing.h"

static void	add_envnode(t_env **list_p, char c, const char *content)
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

static void	add_envvar(t_env *root,const char *envvar, const char *content)
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

static char	**env_copy(const char **envp)
{
	char		**copy_envp;
	int32_t		len;

	len = 0;
	while (envp[len])
		len++;
	copy_envp = (char **)ft_calloc(sizeof (char *), len + 1);
	len = -1;
	while (envp[++len])
		copy_envp[len] = ft_strdup(envp[len]);
	return (copy_envp);
}

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
	root->envp = env_copy(envp);
	return (root);
}

void	append_envp(t_env **envs, char *name, char *content)
{
	ssize_t	i;
	char	**new_envp;
	char	*tmp;
	t_env	*root;

	root = *envs;
	add_envvar(root, name, content);
	new_envp = (char **)ft_calloc(sizeof(char *), ft_arr_len(root->envp) + 2);
	i = -1;
	while (root->envp[++i] && var_exists(root->envp[i]))
		new_envp[i] = root->envp[i];
	if (root->envp[i])
	{
		tmp = root->envp[i];
		root->envp[i] = ft_substr(tmp, 0, ft_strlen(name)); // must be tested
		free(tmp);
	}
	else
		new_envp[i] = ft_strjoin(name, "=");
	tmp = new_envp[i];
	new_envp[i] = ft_strjoin(tmp, content);
	free(tmp);
	free(root->envp);
	root->envp = new_envp;
}
