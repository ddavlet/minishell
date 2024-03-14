#include "../execution.h"

int execute(char **argv, char **envp)
{
	char	*path;

	if (!argv || !envp)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	path = get_path(argv[0], envp);
	if (path == NULL)
		terminate(NULL, NULL, EXIT_FAILURE, "minishell: couldn't find path");
	if (execve(path, argv, envp) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "minishell: execution failure");
	return (0);
}
