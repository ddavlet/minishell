/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_piped.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:46 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:56:19 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_piped(t_cmd2 *cmd)
{
	t_cmd2	*last;
	int		is_piped_flag;

	is_piped_flag = 0;
	last = cmd->cmds;
	while (last)
	{
		cmd_check(last);
		if (last->execution->operation == PIPE_)
			is_piped_flag = 1;
		else
			is_piped_flag = 0;
		if (is_piped_flag && (last == cmd || last->next == cmd))
			return (1);
		last = last->next;
	}
	return (0);
}
