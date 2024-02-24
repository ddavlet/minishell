#include "../builtin/builtin.h"

char	**init_envv(t_env *root);

int	main(int argc, const char *argv[], const char *envp[])
{
	t_cmd	**commands;
	t_env	*env;

	env = init_env(envp);
	append_envp(env, "MZZZ", "TEST");
	append_envp(env, "MZZZ", "");
	append_envp(env, "ZZZ", "test1");
	append_envp(env, "LOGNAME", "test");
	if (!argv[1])
		commands = parse_text("env ", env);
	else
		commands = parse_text(argv[1], env);
	debug_print_env(env, commands[0]->argv[1]);
	builtin_export(commands[0]->argv, env);
	debug_print_env(env, commands[0]->argv[1]);
	builtin_unset(commands[0]->argv, env);
	debug_print_env(env, commands[0]->argv[1]);
	builtin_pwd(commands[0]->argv, env);
	builtin_env(commands[0]->argv, env);
	builtin_echo(commands[0]->argv, env);
	builtin_cd(commands[0]->argv, env);
	terminate_commands(commands);
	terminate_env(env);
	(void)argc;
	(void)argv;
	(void)commands;
	return (0);
}
