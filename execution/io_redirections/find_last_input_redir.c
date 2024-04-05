#include "../execution.h"

t_fd_state	*last_input_redir(t_cmd2 *cmd)
{
	t_redir		*redir;
	t_fd_state	*input_fd_state;
    t_env        *shell_env;

	cmd_check(cmd);
	redir = cmd->execution->redirections;
	if (!redir)
		return (NULL);
    shell_env = cmd->execution->shell_env;
	input_fd_state = NULL;
	while (redir)
	{
		if (input_fd_state && input_fd_state->fd != STDIN_FILENO
			&& (redir->redir_sym == RED_INP || redir->redir_sym == HEAR_DOC))
			close_fd(input_fd_state);
		if (redir->redir_sym == RED_INP)
			input_fd_state = input_redirection(redir->redir_name);
		else if (redir->redir_sym == HEAR_DOC)
			input_fd_state = here_document(redir->redir_name, shell_env);
		redir = redir->next;
	}
	return (input_fd_state);
}
