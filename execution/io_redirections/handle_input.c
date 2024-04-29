/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:30 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 16:24:25 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_fd_state	*input_redirection(const char *file_name)
{
	int			fd;
	t_fd_state	*fd_state;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (msg_error("open")); // catch
	fd_state = initialize_fd_state(fd);
	if (!fd_state)
	{
		close(fd);
		ft_putendl_fd("input redirection failed", 2);
	}
	return (fd_state);
}
