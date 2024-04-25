/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:33:41 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/24 15:38:30 by vketteni         ###   ########.fr       */
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

t_cmd2	*create_cmds(int argc, char *argv[], t_env *shell_env)
{
	t_token	*tokens;
	char	*prompt;

	if (is_subshell(argc, argv))
		tokens = tokenizer(argv[2]);
	else
	{
		prompt = shell_prompt(shell_env);
		tokens = tokenizer(prompt);
		free(prompt);
	}
	return (parser(tokens, shell_env));
}

int	main(int argc, char *argv[], const char *envp[])
{
	t_env	*shell_env;
	t_cmd2	*cmds;

	shell_env = initialize_shell(envp);
	if (!shell_env)
		exit(1);
	while (1)
	{
		g_signal = 0;
		configure_signals_shell_input();
		cmds = create_cmds(argc, argv, shell_env);
		execution(cmds);
		if (is_subshell(argc, argv))
			terminate_shell(shell_env, EXIT_SUCCESS, NULL);
	}
	return (0);
}
