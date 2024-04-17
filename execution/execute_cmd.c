#include "execution.h"
#include <errno.h>

int	execute_command(t_cmd2 *cmd)
{
	const char 	*path;
	char 	*const *argv;
	char 	*const *envp;

	cmd_check(cmd);
	envp = cmd->execution->shell_env->envp;
	argv = (char *const*)cmd->execution->argv;
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = (const char *)build_path_from_env(argv[0], cmd->execution->shell_env);
		if (path == NULL)
			return (terminate(cmd, 127, "minishell: couldn't find path"));
	}
	else
		path = argv[0];
	execve(path, argv, envp);
	return (0);
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
    {
        if (is_builtin(cmd))
        {
            builtin_router(cmd);
            exit(cmd->execution->exit_status);
        }
        else
			execute_command(cmd);
    }
}
