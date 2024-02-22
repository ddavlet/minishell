#include "../execution.h"

void	determine_output_fd(t_executor *executor, int cmd_index)
{
	t_redir *redir;

	if (!executor || !executor->cmds || !executor->cmds[cmd_index])
		return (-1);
	redir = executor->cmds[cmd_index]->redirs;
	if (redirs == NULL)
		return (executor->out_fd);
	while (redir)
	{
		if (redir->redir_sym == RED_OUT)
			handle_truncate_redirection(redir->redir_name);
		else if (redir->redir_sym == APP_OUT)
			handle_append_redirection(redir->redir_name);
		redir = redir->next;
	}
}
