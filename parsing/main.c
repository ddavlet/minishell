#include "../builtin/builtin.h"
#include "./wildcard/wildcard.h"

char	**init_envv(t_env *root);
void	find_wildcard(char	***matches, char *letters, t_tree *root);

char *generate_random_filename()
{
	char *filename = (char *)malloc(4 + 1); // Allocate memory for the filename
	if (filename == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Define a pool of characters to choose from
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	// Generate random characters for the filename
	for (int i = 0; i < 4; ++i)
	{
		int index = rand() % (sizeof(charset) - 1);
		filename[i] = charset[index];
	}
	filename[4] = '\0'; // Null-terminate the string

	return filename;
}

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
		commands = parse_text("(echo <testin >testout ) (test && echo < testin > testout test)| echo test", env);
	else
		commands = parse_text(argv[1], env);
	debug_print_cmd(commands);
	terminate_commands(commands);
	terminate_env(env);
	(void)argc;
	(void)argv;
	(void)commands;
	return (0);
}
