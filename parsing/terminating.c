#include "parsing.h"

int	terminate_commands(t_cmd **commands)
{
	int	i;

	i = 0;
	if (commands)
	{
		while (commands[i])
			free(commands[i++]);
	}
	free(commands);
	return (0);
}

int	terminate_tokens(char **ptr)
{
	ssize_t	i;

	i = 0;
	if (!ptr)
		return (0); //is that error??
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (0);
}

void	terminate_env(t_env *root)
{
	t_env	*tmp;

	if (!root)
		return ;
	while (root)
	{
		terminate_env(root->child);
		tmp = root;
		root = root->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}
