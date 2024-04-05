#include "execution.h"

int	builtin_router(t_cmd2 *cmd)
{
	char	*builtin;
	t_env	*shell_env;
	int		exit_status;

	cmd_check(cmd);
	exit_status = cmd->execution->exit_status;
	shell_env = cmd->execution->shell_env;
	builtin = cmd->execution->argv;
	if (ft_strncmp(builtin[0], "cd", ft_strlen("cd") + 1) == 0)
		exit_status = builtin_cd(builtin, shell_env);
	else if (ft_strncmp(builtin[0], "echo", ft_strlen("echo") + 1) == 0)
		exit_status = builtin_echo(builtin, shell_env);
	else if (ft_strncmp(builtin[0], "env", ft_strlen("env") + 1) == 0)
		exit_status = builtin_env(builtin, shell_env);
	else if (ft_strncmp(builtin[0], "exit", ft_strlen("exit") + 1) == 0)
		exit_status = builtin_exit(builtin, shell_env);
	else if (ft_strncmp(builtin[0], "pwd", ft_strlen("pwd") + 1) == 0)
		exit_status = builtin_pwd(builtin, shell_env);
	else if (ft_strncmp(builtin[0], "unset", ft_strlen("unset") + 1) == 0)
		exit_status = builtin_unset(builtin, shell_env);
	else if (ft_strncmp(builtin[0], "export", ft_strlen("export") + 1) == 0)
		exit_status = builtin_export(builtin, shell_env);
	else
		exit_status = EXIT_FAILURE;
}
