/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:33:41 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/26 10:28:09 by ddavlety         ###   ########.fr       */
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
	char	*exit_code;
	int		exit_code_int;

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
		{
			exit_code = get_variable_value("LAST_EXIT_STATUS", shell_env);
			exit_code_int = ft_atoi(exit_code);
			free(exit_code);
			terminate_shell(shell_env, exit_code_int, NULL);
		}
	}
	return (0);
}
