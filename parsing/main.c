#include "parsing.h"

int	main(int argc, const char *argv[], const char *envp[])
{
	t_cmd	**commands;
	t_env	*env;

	env = init_env(envp);
	append_envp(&env, "MZZZ", "TEST");
	debug_print_env(env, "MZZZ");
	if (!argv[1])
		commands = parse_text("'e'ch'o' $ USER*test | echo <<infile test2 \
			|| echo test3 > outfile || echo test4  ", env);
	else
		commands = parse_text(argv[1], env);
	debug_print_env(env, commands[0]->argv[1]);
	builtin_export(commands[0]->argv, env);
	debug_print_env(env, commands[0]->argv[1]);
	builtin_unset(commands[0]->argv, env);
 	debug_print_env(env, commands[0]->argv[1]);
	builtin_pwd(commands[0]->argv, env);
	builtin_env(commands[0]->argv, env);
	terminate_commands(commands);
	terminate_env(env);
	(void)argc;
	(void)argv;
	(void)commands;
	return (0);
}
