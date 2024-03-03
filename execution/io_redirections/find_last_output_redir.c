#include "../execution.h"

int	last_output_redir(t_executor *exec)
{
	t_redir *redir;
    int     out_fd;

	if (!exec || !exec->cmds || !exec->cmds[exec->command_index])
		return (-1);
    out_fd = 1;
	redir = exec->cmds[exec->command_index]->redirs;
	if (redir == NULL)
		return (out_fd);
	while (redir)
	{
		if (redir->redir_sym == RED_OUT)
			out_fd = handle_truncate_redirection(redir->redir_name);
		else if (redir->redir_sym == APP_OUT)
			out_fd = handle_append_redirection(redir->redir_name);
		redir = redir->next;
	}
    return (out_fd);
}
