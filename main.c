#include "main.h"

int	g_signal;

int	main(int argc, char *argv[], const char *envp[])
{
	t_cmd2	*cmds;
	t_token	*tokens;
	t_env	*shell_env;
	char	*prompt;

	shell_env = initialize_shell(envp);
	if (!shell_env)
		exit(1);
	printf("main pid: %d\n", getpid());
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
		printf("executed: %d\n", getpid());
		if (is_subshell(argc, argv))
			terminate_shell(shell_env, EXIT_SUCCESS, NULL);
		printf("after subshell check: %d\n", getpid());
	}
	return (0);
}
