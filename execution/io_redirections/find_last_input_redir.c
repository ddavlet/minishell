#include "../execution.h"

int	last_input_redir(t_executor *exec, t_scope *scope)
{
	t_redir	*redir;
	int		in_fd;

	if (!exec || !exec->cmds || !exec->cmds[exec->command_index]
		|| !exec->cmds[exec->command_index]->env)
		return (-1);
	in_fd = 0;
	redir = exec->cmds[exec->command_index]->redirs;
	if (redir == NULL)
		return (in_fd);
	while (redir)
	{
		if (redir->redir_sym == RED_INP)
			in_fd = handle_input_redirection(redir->redir_name);
		else if (redir->redir_sym == HEAR_DOC)
			in_fd = handle_here_document(redir->redir_name,
					exec->cmds[exec->command_index]->env, scope);
		redir = redir->next;
	}
	return (in_fd);
}
