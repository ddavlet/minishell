#include "execution.h"

int	child_process(t_cmd2 *cmd)
{
	char	*path;
	char	**argv;
	char	**envp;

	envp = cmd->shell_env->envp;
	argv = cmd->argv;
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = build_path_from_env(argv[0], cmd->shell_env);
		if (path == NULL)
        {
            ft_putendl_fd("minishell: couldn't find path", STDERR_FILENO);
            return (-1);
        }
	}
	else
		path = argv[0];
	return(execve(path, argv, envp));
}

int	execute_cmd(t_cmd2 *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
    {
        ft_putendl_fd("failed to fork", STDERR_FILENO);
        return (-1);
    }
	else if (cmd->pid == 0)
		return (child_process(cmd));
}
