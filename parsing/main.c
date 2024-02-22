#include "parsing.h"

int	main(int argc, const char *argv[], const char *envp[])
{
	t_cmd	**commands;
	t_env	*env;

	env = init_env(envp);
	append_envp(&env, "MZZZ", "TEST");
	debug_print_env(env, "MZZZ");
	commands = parse_text(argv[1], env);
	debug_print_cmd(commands);
	terminate_commands(commands);
	terminate_env(env);
	(void)argc;
	(void)commands;
	return (0);
}
