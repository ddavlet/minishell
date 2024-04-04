#include "../execution.h"

t_fd_state	*last_input_redir(t_cmd2 *cmd)
{
	t_redir		*redir;
	t_fd_state	*input_fd_state;

	if (!cmd)
		return (NULL);
	redir = cmd->redirections;
	if (!redir)
		return (NULL);
	input_fd_state = NULL;
	while (redir)
	{
		if (input_fd_state && input_fd_state->fd != STDIN_FILENO
			&& (redir->redir_sym == RED_INP || redir->redir_sym == HEAR_DOC))
			close_fd(input_fd_state);
		if (redir->redir_sym == RED_INP)
			input_fd_state = input_redirection(redir->redir_name);
		else if (redir->redir_sym == HEAR_DOC)
			input_fd_state = here_document(redir->redir_name, cmd->shell_env);
		redir = redir->next;
	}
	return (input_fd_state);
}
