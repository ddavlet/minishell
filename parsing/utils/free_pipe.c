/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:19:25 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/28 14:19:26 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_pipe(t_pipe *pipe)
{
	if (pipe)
	{
		close_pipe(pipe);
		free(pipe->pipe_fd);
		free(pipe->read);
		free(pipe->write);
		free(pipe);
	}
}