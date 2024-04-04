#include "../execution.h"

t_fd_state	*last_output_redir(t_cmd2 *cmd)
{
	t_redir		*redir;
	t_fd_state	*output_fd_state;

	if (!cmd)
		return (NULL);
	redir = cmd->redirections;
	if (redir == NULL)
		return (NULL);
	output_fd_state = NULL;
	while (redir)
	{
		if (output_fd_state && output_fd_state->fd != STDOUT_FILENO
			&& (redir->redir_sym == RED_OUT || redir->redir_sym == APP_OUT))
			close_fd(output_fd_state);
		if (redir->redir_sym == RED_OUT)
			output_fd_state = truncate_redirection(redir->redir_name);
		else if (redir->redir_sym == APP_OUT)
			output_fd_state = append_redirection(redir->redir_name);
		redir = redir->next;
	}
	return (output_fd_state);
}
