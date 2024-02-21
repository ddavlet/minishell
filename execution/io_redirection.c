#include "execution.h"

static int	handle_input_redirection(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		msg_error("open");
	return (fd);
}

static int	handle_truncate_redirection(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		msg_error("open");
	return (fd);
}

static int	handle_append_redirection(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		msg_error("open");
	return (fd);
}

void	determine_input_fd(t_executor *executor, int cmd_index)
{
	t_redir *redir;

	if (!executor || !executor->cmds || !executor->cmds[cmd_index])
		return (-1);
	if (executor->cmds[cmd_index]->redirs == NULL)
		return (executor->in_fd);
	redir = executor->cmds[cmd_index]->redirs;
	while (redir)
	{
		if (redir->redir_sym == RED_INP)
			handle_input_redirection(redir->redir_name);
		else if (redir->redir_sym == HEAR_DOC)
			handle_here_document(redir->redir_name);
		redir = redir->next;
	}
}

void	determine_output_fd(t_executor *executor, int cmd_index)
{
	t_redir *redir;

	if (!executor || !executor->cmds || !executor->cmds[cmd_index])
		return (-1);
	if (executor->cmds[cmd_index]->redirs == NULL)
		return (executor->out_fd);
	redir = executor->cmds[cmd_index]->redirs;
	while (redir)
	{
		if (redir->redir_sym == RED_OUT)
			handle_truncate_redirection(redir->redir_name);
		else if (redir->redir_sym == APP_OUT)
			handle_append_redirection(redir->redir_name);
		redir = redir->next;
	}
}