#include "../execution.h"

int	find_last_input_redir(t_executor *executor, int cmd_index)
{
	t_redir	*redir;
	int		in_fd;

	if (!executor || !executor->cmds || !executor->cmds[cmd_index]
		|| !executor->cmds[cmd_index]->env)
		return (-1);
	in_fd = 0;
	redir = executor->cmds[cmd_index]->redirs;
	if (redir == NULL)
		return (in_fd);
	while (redir)
	{
		if (redir->redir_sym == RED_INP)
			in_fd = handle_input_redirection(redir->redir_name);
		else if (redir->redir_sym == HEAR_DOC)
			in_fd = handle_here_document(redir->redir_name, executor->cmds[cmd_index]->env, executor);
		redir = redir->next;
	}
	return (in_fd);
}
