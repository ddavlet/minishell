/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:41 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/19 11:34:22 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"

t_fd_state	*initialize_fd_state(int fd)
{
	t_fd_state	*fd_state;

	fd_state = (t_fd_state *)ft_calloc(1, sizeof(t_fd_state));
	if (!fd_state)
		return (NULL);
	fd_state->fd = fd;
	fd_state->is_open = 1;
	return (fd_state);
}

static t_pipe	*initialize_pipe(void)
{
	int		*pipe_fd;
	t_pipe	*p;

	pipe_fd = ft_calloc(2, sizeof(int));
	if (!pipe_fd)
		return (NULL);
	p = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!p)
	{
		free(pipe_fd);
		return (NULL);
	}
	if (pipe(pipe_fd) == -1)
	{
		free(pipe_fd);
		return (NULL);
	}
	p->pipe_fd = pipe_fd;
	return (p);
}

t_pipe	*create_pipe(void)
{
	t_pipe	*pipe;

	pipe = initialize_pipe();
	if (!pipe)
		return (NULL);
	pipe->read = initialize_fd_state(pipe->pipe_fd[0]);
	if (!(pipe->read))
	{
		free(pipe);
		return (NULL);
	}
	pipe->write = initialize_fd_state(pipe->pipe_fd[1]);
	if (!(pipe->write))
	{
		free(pipe->read);
		free(pipe);
		return (NULL);
	}
	pipe->write->pipe = pipe;
	pipe->read->pipe = pipe;
	return (pipe);
}
