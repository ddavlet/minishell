/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:39 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/19 11:30:08 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	close_redir(t_fd_state *fd_state)
{
	if (fd_state)
	{
		if (fd_state->pipe)
			close_pipe(fd_state->pipe);
		else
		{
			close_fd(fd_state);
			free(fd_state);
		}
    }
}
