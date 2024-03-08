#include "../execution.h"

t_fd_state	*last_output_redir(t_executor *exec)
{
	t_redir     *redir;
    t_fd_state  *output_fd_state;

	if (!exec || !exec->cmds || !exec->cmds[exec->command_index])
		return (NULL);
	redir = exec->cmds[exec->command_index]->redirs;
	if (redir == NULL)
		return (exec->output_fd);
    output_fd_state = NULL;
	while (redir)
	{
		if (redir->redir_sym == RED_OUT)
			output_fd_state = truncate_redirection(redir->redir_name);
		else if (redir->redir_sym == APP_OUT)
			output_fd_state = append_redirection(redir->redir_name);
		redir = redir->next;
	}
    if (!output_fd_state)
        terminate(NULL, NULL, EXIT_FAILURE, "couldn't find output redirection");
    return (output_fd_state);
}
