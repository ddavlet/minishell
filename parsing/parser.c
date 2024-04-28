/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:00 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/25 15:57:12 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd2	*parser(t_token *tokens, t_env *shell_env)
{
	t_cmd2	*cmds;

	if (syntax_check(tokens) == -1)
	{
		free_tokens(tokens);
		return (NULL);
	}
	cmds = initialize_commands(tokens, shell_env);
	if (!cmds)
	{
		terminate_parsing(tokens, shell_env, NULL,
			"minishell: failed to parse command line");
		return (NULL);
	}
	expand_wildcards(cmds, shell_env);
	return (cmds);
}
