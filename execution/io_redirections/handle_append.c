/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:20 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 16:24:24 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_fd_state	*append_redirection(const char *file_name)
{
	int			fd;
	t_fd_state	*fd_state;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (msg_error("open")); // catch
	fd_state = initialize_fd_state(fd);
	if (!fd_state)
	{
		close(fd);
		ft_putendl_fd("append redirection failed", 2);
	}
	return (fd_state);
}
