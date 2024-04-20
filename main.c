/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:33:41 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/20 11:41:40 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_signal;

int	is_subshell(int argc, char **argv)
{
	if (argc == 3 && !ft_strncmp(argv[1], "-n", 3))
		return (1);
	return (0);
}

int	main(int argc, char *argv[], const char *envp[])
{
	t_cmd2	*cmds;
	t_token	*tokens;
	t_env	*shell_env;
	char	*prompt;

	shell_env = initialize_shell(envp);
	if (!shell_env)
		exit(1);
	while (1)
	{
		g_signal = 0;
		configure_signals_shell_input();
		if (is_subshell(argc, argv))
			tokens = tokenizer(argv[2]);
		else
		{
			prompt = shell_prompt(shell_env);
			tokens = tokenizer(prompt);
			free(prompt);
		}
		cmds = parser(tokens, shell_env);
		execution(cmds);
		if (is_subshell(argc, argv))
			terminate_shell(shell_env, EXIT_SUCCESS, NULL);
	}
	return (0);
}
