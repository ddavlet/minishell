#include "execution.h"

int	child_process(t_executor *exec)
{
	char	*path;
	char	**argv;
	char	**envp;

	envp = exec->envp;
	argv = get_current_cmd(exec)->argv;
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = build_path_from_env(argv[0], get_current_cmd(exec)->env);
		if (path == NULL)
			terminate(exec, EXIT_FAILURE, "minishell: couldn't find path");
	}
	else
		path = argv[0];
	if (execve(path, argv, envp) == -1)
		terminate(exec, EXIT_FAILURE, "minishell: execution failure");
	return (0);
}

void	execute_cmd(t_executor *exec)
{
    int index;

    index = exec->command_index;
	set_pid(exec, index, fork());
	if (get_pid(exec, index) == -1)
		terminate(exec, EXIT_FAILURE, "failed to fork");
	else if (get_pid(exec, index) == 0)
		child_process(exec);
}
