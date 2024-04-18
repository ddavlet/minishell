#include "execution.h"

int	execute_command(t_cmd2 *cmd)
{
	const char	*path;

	char *const *argv;
	char *const *envp;
	cmd_check(cmd);
	envp = cmd->execution->shell_env->envp;
	argv = (char *const *)cmd->execution->argv;
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = (const char *)build_path_from_env(argv[0],
				cmd->execution->shell_env);
		if (path == NULL)
			terminate(cmd, 127, "minishell: couldn't find path");
	}
	else
		path = argv[0];
	if (execve(path, argv, envp) == -1)
		terminate_shell(cmd->execution->shell_env, 126,
			"minishell: permission denied");
	return (0);
}

int	execute_cmd(t_cmd2 *cmd)
{
	pid_t	pid;

	cmd_check(cmd);
	pid = fork();
	cmd->execution->pid = pid;
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
			return (execute_command(cmd));
	}
	if (cmd->execution->pipe)
		close_pipe(cmd->execution->pipe);
	return (0);
}
