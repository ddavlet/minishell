/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:43 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:31:45 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	cmd_check(t_cmd2 *cmd)
{
	if (!cmd)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing command");
	if (!cmd->execution)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing execution");
	if (!cmd->execution->argv)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing argv");
	if (!cmd->execution->shell_env)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing shell environment");
}
