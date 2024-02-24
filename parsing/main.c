#include "parsing.h"

char	**init_envv(t_env *root);

int	main(int argc, const char *argv[], const char *envp[])
{
	t_cmd	**commands;
	t_env	*env;

	env = init_env(envp);
	append_envp(env, "MZZZ", "TEST");
	append_envp(env, "MZZZ", "");
	append_envp(env, "ZZZ", "");
	append_envp(env, "LOGNAME", "test");
	debug_print_env(env, "MZZZ");
	if (!argv[1])
		commands = parse_text("'e'ch'o' $ USER*test | echo <<infile test2 \
			|| echo test3 > outfile || echo test4  ", env);
	else
		commands = parse_text(argv[1], env);
	debug_print_cmd(commands);
	debug_print_array_strings(env->envp);
	terminate_commands(commands);
	terminate_env(env);
	(void)argc;
	(void)argv;
	(void)commands;
	return (0);
}
