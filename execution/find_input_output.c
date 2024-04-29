/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_input_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:22:12 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 19:22:14 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	find_input_redirection(t_cmd2 *cmd)
{
	t_redir	*redir;

	redir = cmd->execution->redirections;
	while (redir)
	{
		if (redir->redir_sym == RED_INP || redir->redir_sym == HERE_DOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	find_output_redirection(t_cmd2 *cmd)
{
	t_redir	*redir;

	redir = cmd->execution->redirections;
	while (redir)
	{
		if (redir->redir_sym == RED_OUT || redir->redir_sym == APP_OUT)
			return (1);
		redir = redir->next;
	}
	return (0);
}
