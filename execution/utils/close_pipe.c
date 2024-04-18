/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:36 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 14:03:38 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	close_pipe(t_pipe *pipe)
{
	if (pipe)
	{
		if (pipe->read->is_open)
			close_fd(pipe->read);
		if (pipe->write->is_open)
			close_fd(pipe->write);
		free(pipe->pipe_fd);
		free(pipe->read);
		free(pipe->write);
		free(pipe);
	}
}
