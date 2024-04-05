#include "execution.h"

void	child_process(t_cmd2 *cmd)
{
	char	*path;
	char	**argv;
	char	**envp;

    cmd_check(cmd);
	envp = cmd->execution->shell_env->envp;
	argv = cmd->execution->argv;
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = build_path_from_env(argv[0], cmd->execution->shell_env);
		if (path == NULL)
            terminate(cmd, EXIT_FAILURE, "minishell: couldn't find path");
	}
	else
		path = argv[0];
	execve(path, argv, envp);
}

void	execute_cmd(t_cmd2 *cmd)
{
    pid_t   pid;

    cmd_check(cmd);
	pid = cmd->execution->pid;
    pid = fork();
	if (pid == -1)
        terminate(cmd, EXIT_FAILURE, "minishell: failed to fork");
	else if (pid == 0)
		child_process(cmd);
}
