#include "../execution.h"


void	determine_input_fd(t_executor *executor, int cmd_index)
{
	t_redir *redir;

	if (!executor || !executor->cmds || !executor->cmds[cmd_index])
		return (-1);
	redir = executor->cmds[cmd_index]->redirs;
	if (redirs == NULL)
		return (executor->in_fd);
	while (redir)
	{
		if (redir->redir_sym == RED_INP)
			handle_input_redirection(redir->redir_name);
		else if (redir->redir_sym == HEAR_DOC)
			handle_here_document(redir->redir_name);
		redir = redir->next;
	}
}

