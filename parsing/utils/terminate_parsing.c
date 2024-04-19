/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:31 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:45:08 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	terminate_parsing(t_token *tokens, t_env *shell_env, t_cmd2 *cmds,
		char *msg)
{
	free_cmds(cmds);
	free_tokens(tokens);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	append_envp(shell_env, "LAST_EXIT_STATUS", "2");
	return (EXIT_FAILURE);
}
