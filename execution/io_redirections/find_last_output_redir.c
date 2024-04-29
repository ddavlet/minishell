/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last_output_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:15 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 16:28:47 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_fd_state	*last_output_redir(t_cmd2 *cmd)
{
	t_redir		*redir;
	t_fd_state	*output_fd_state;

	cmd_check(cmd);
	redir = cmd->execution->redirections;
	if (redir == NULL)
		return (NULL);
	output_fd_state = NULL;
	while (redir)
	{
		if (output_fd_state && output_fd_state->fd != STDOUT_FILENO
			&& (redir->redir_sym == RED_OUT || redir->redir_sym == APP_OUT))
		{
			close_fd(output_fd_state);
			free(output_fd_state);
		}
		if (redir->redir_sym == RED_OUT)
			output_fd_state = truncate_redirection(redir->redir_name);
		else if (redir->redir_sym == APP_OUT)
			output_fd_state = append_redirection(redir->redir_name);
		if (!output_fd_state)
			break ;
		redir = redir->next;
	}
	return (output_fd_state);
}
