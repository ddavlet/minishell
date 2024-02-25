#include "parsing.h"

void	*terminate_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
    (void)i;
	if (!cmd)
		return (NULL); // ERROR!
	if (cmd->com)
		free(cmd->com);
	terminate_ptr_str(cmd->argv);
	terminate_redirs(cmd->redirs);
	free(cmd);
	return (NULL);
}

void	*terminate_commands(t_cmd **commands)
{
	int	i;

	i = 0;
	if (!commands)
		return (0); //is that error??
	while (commands[i])
	{
		free(commands[i]->com);
		terminate_ptr_str(commands[i]->argv);
		terminate_redirs(commands[i]->redirs);
		terminate_env(commands[i]->env);
		free(commands[i++]);
	}
	free(commands);
	return (0);
}

int	terminate_ptr_str(char **ptr)
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
		if (tmp->envp)
			terminate_ptr_str(tmp->envp);
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

void	terminate_redirs(t_redir *redir_l)
{
	t_redir	*tmp;

	if (!redir_l)
		return ;
	while (redir_l)
	{
		tmp = redir_l;
		redir_l = redir_l->next;
		if (tmp->redir_name)
			free(tmp->redir_name);
		free(tmp);
	}
}
