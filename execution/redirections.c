#include "execution.h"

// Definition of ft_mkstemp function is:
// int	ft_mkstemp(char *template)

int ft_mkstemp(char *template)
{
    int fd;
    char *tmp;
    char *tmp2;
    char *tmp3;
    int i;
    char *template = "/tmp/cmdtmp"; // Temporary file template
    tmp = ft_strdup(template);
    if (tmp == NULL)
        return (-1);
    i = 0;
    while (i < 100)
    {
        tmp2 = ft_itoa(i);
        tmp3 = ft_strjoin(tmp, tmp2);
        if (tmp2 == NULL)
        {
            free(tmp);
            free(tmp2);
            return (-1);
        }
        fd = open(tmp2, O_CREAT | O_EXCL | O_RDWR, 0600);
        if (fd != -1)
        {
            free(tmp);
            free(tmp2);
            free(tmp3);
            return (fd);
        }
        free(tmp2);
        free(tmp3);
        i++;
    }
    return (-1);
}

int handle_here_document(const char *delimiter)
{
    int fd = mkstemp(template);
    if (fd == -1)
    {
        perror("mkstemp");
        return -1;
    }
    unlink(template); // Ensure the file is removed when closed
    char *line = readline("%% ");
    while ((line ) != NULL)
    {
        if (strcmp(line, delimiter) == 0)
        {
            // Check if the line is the delimiter
            free(line);
            break; // Delimiter reached, stop reading input
        }
        write(fd, line, strlen(line)); // Write the line to the file
        write(fd, "\n", 1); // Add newline character after each line
        free(line);
    }
    free(line);
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        // Reset file descriptor position
        perror("lseek");
        close(fd);
        return -1;
    }
    return fd;
}

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