#include "../builtin/builtin.h"
#include "./wildcard/wildcard.h"

char	**init_envv(t_env *root);
void	router(char	**matches, char *letters, t_tree *root);

char *generate_random_filename() {
    char *filename = (char *)malloc(4 + 1); // Allocate memory for the filename
    if (filename == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Define a pool of characters to choose from
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Generate random characters for the filename
    for (int i = 0; i < 4; ++i) {
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

	// char *file_names[10];
    // // Initialize array with random filenames
    // for (int i = 0; i < 10; i++) {
    //     file_names[i] = generate_random_filename();
    // }
	char	**matches = NULL;
	char	letters[] = "us*r";
	t_tree *tree = init_tree(&argv[1]);
	router(matches, letters, tree);
	debug_print_array_strings(matches);
	terminate_commands(commands);
	terminate_env(env);
	(void)argc;
	(void)argv;
	(void)commands;
	return (0);
}
