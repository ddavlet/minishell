#include "main.h"

int	g_signal;

int	main(int argc, char *argv[], const char *envp[])
{
	t_cmd2	*cmds;
	t_token	*tokens;
	t_env	*shell_env;

	shell_env = initialize_shell(envp);
	while (1)
	{
		g_signal = 0;
		configure_signals_shell_input();
		if (is_subshell(argc, argv))
			tokens = tokenizer(argv[2]);
		else
		{
			const char *prompt = shell_prompt(shell_env);
			tokens = tokenizer(prompt);
			free((char *)prompt);
		}
		cmds = parser(tokens, shell_env);
		execution(cmds);
		if (is_subshell(argc, argv))
			terminate_shell(shell_env, EXIT_SUCCESS, NULL);
	}
	return (0);
}
