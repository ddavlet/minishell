/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_document.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:22 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/27 18:01:36 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	here_doc_warning(const char *delimiter)
{
	if (!g_signal)
	{
		write(1,
			"minishell: warning: here-document "
			"delimited by end-of-file (wanted `", 68);
		write(1, delimiter, ft_strlen(delimiter));
		write(1, "')\n", 3);
	}
}

void	here_document_loop(t_pipe *pipe, const char *delimiter,
		t_env *shell_env)
{
	const char	*line;
	const char	*tmp;

	line = (const char *)readline("heredoc> ");
	while (line && g_signal != SIGINT)
	{
		if (!ft_strncmp(line, delimiter, ft_strlen(line) + 1)
			&& ft_strlen(line))
			break ;
		tmp = replace_variables(line, shell_env);
		free((void *)line);
		line = tmp;
		write(pipe->write->fd, line, ft_strlen(line));
		write(pipe->write->fd, "\n", 1);
		free((void *)line);
		line = (const char *)readline("heredoc> ");
	}
	if (!line)
		here_doc_warning(delimiter);
	free((void *)line);
}

t_pipe	*here_document(const char *delimiter, t_env *shell_env)
{
	t_pipe	*pipe;

	if (g_signal == SIGINT)
		return (NULL);
	configure_signals_heardoc();
	pipe = create_pipe();
	if (!pipe)
		return (NULL);
	here_document_loop(pipe, delimiter, shell_env);
	close_fd(pipe->write);
	return (pipe);
}

void	handle_heredoc_before_execution(t_cmd2 *cmds, t_env *shell_env)
{
	t_cmd2	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->execution->redirections;
		while (redir)
		{
			if (redir->redir_sym == HERE_DOC)
			{
				if (cmd->execution->heredoc)
					close_pipe(cmd->execution->heredoc);
				cmd->execution->heredoc = here_document(redir->redir_name,
						shell_env);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
