#include "parsing.h"

static void	add_envnode(t_env **list_p, char c, const char *content)
{
	t_env	*last;
	t_env	*new_node;

	last = *list_p;
	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return ; // dela with this return
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

static void	add_envvar(t_env *root, const char *envvar, const char *content)
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
		{
			free((*child_p)->content);
			(*child_p)->content = ft_strdup(content);
			(*child_p)->exists = true;
		}
		envvar++;
	}
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
	root->envp = arrstr_copy(envp);
	return (root);
}

void	append_envp(t_env *root, char *name, char *content)
{
	add_envvar(root, name, content);
	terminate_ptr_str(root->envp);
	root->envp = init_envv(root);
}

void	add_path(t_env *root, char *path)
{
	char	*old_path;
	char	*new_path;

	old_path = get_shell_variable(root, "PATH");
	if (ft_strnstr(old_path, path, ft_strlen(path)))
		return ;
	new_path = ft_strjoin_free(old_path, ":");
	new_path = ft_strjoin_free(new_path, path);
	append_envp(root, "PATH", new_path);
}
