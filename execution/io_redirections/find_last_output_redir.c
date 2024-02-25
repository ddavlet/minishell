#include "../execution.h"

int	find_last_output_redir(t_executor *executor, int cmd_index)
{
	t_redir *redir;
    int     out_fd;

	if (!executor || !executor->cmds || !executor->cmds[cmd_index])
		return (-1);
    out_fd = 1;
	redir = executor->cmds[cmd_index]->redirs;
	if (redir == NULL)
		return (out_fd);
	while (redir)
	{
		if (redir->redir_sym == RED_OUT)
			executor->out_fd = handle_truncate_redirection(redir->redir_name);
		else if (redir->redir_sym == APP_OUT)
			executor->out_fd = handle_append_redirection(redir->redir_name);
		redir = redir->next;
	}
    return (out_fd);
}
