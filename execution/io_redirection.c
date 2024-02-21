#include "execution.h"

int	determine_input_fd(t_cmd *cmd, int in_fd)
{
	t_redir *redir;

	if (cmd->redirs == NULL)
		return (in_fd);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->redir_sym == RED_INP)
		{
			in_fd = open(redir->redir_name, O_RDONLY);
			if (in_fd == -1)
				msg_error("open");
			return (in_fd);
		}
		else if (redir->redir_sym == HEAR_DOC)
		{
			in_fd = handle_here_document(redir->redir_name);
			if (in_fd == -1)
				msg_error("handle_here_document");
			return (in_fd);
		}
		else
			break;
		redir = redir->next;
	}
	msg_error("determine_input_fd");
	return (-1);
}

int	determine_output_fd(t_cmd *cmd, int out_fd)
{
	t_redir *redir;

	if (cmd->redirs == NULL)
		return (out_fd);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->redir_sym == RED_OUT)
		{
			out_fd = open(redir->redir_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out_fd == -1)
				msg_error("open");
			return (out_fd);
		}
		else if (redir->redir_sym == APP_OUT)
		{
			out_fd = open(redir->redir_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out_fd == -1)
				msg_error("open");
			return (out_fd);
		}
		else
			break;
		redir = redir->next;
	}
	msg_error("determine_output_fd");
	return (-1);
}