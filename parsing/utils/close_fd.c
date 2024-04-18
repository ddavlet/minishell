/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:05 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 17:46:23 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	close_fd(t_fd_state *fd_state)
{
	if (!fd_state)
	{
		ft_putendl_fd("can't close file descriptor," \
			"missing state", STDERR_FILENO);
		return ;
	}
	if (fd_state->is_open == 0)
		ft_putendl_fd("file descriptor already closed", STDERR_FILENO);
	else if (close(fd_state->fd) == -1)
		ft_putendl_fd("failed to close file descriptor", STDERR_FILENO);
	fd_state->is_open = 0;
}
