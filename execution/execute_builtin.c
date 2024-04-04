#include "execution.h"

int	builtin_router(t_cmd2 *cmd)
{
	char	*builtin;

	builtin = cmd->argv[0];
	if (ft_strncmp(builtin, "cd", ft_strlen("cd") + 1) == 0)
		return (builtin_cd(cmd->argv, cmd->shell_env));
	else if (ft_strncmp(builtin, "echo", ft_strlen("echo") + 1) == 0)
		return (builtin_echo(cmd->argv, cmd->shell_env));
	else if (ft_strncmp(builtin, "env", ft_strlen("env") + 1) == 0)
		return (builtin_env(cmd->argv, cmd->shell_env));
	else if (ft_strncmp(builtin, "exit", ft_strlen("exit") + 1) == 0)
		return (builtin_exit(cmd->argv, cmd->shell_env));
	else if (ft_strncmp(builtin, "pwd", ft_strlen("pwd") + 1) == 0)
		return (builtin_pwd(cmd->argv, cmd->shell_env));
	else if (ft_strncmp(builtin, "unset", ft_strlen("unset") + 1) == 0)
		return (builtin_unset(cmd->argv, cmd->shell_env));
	else if (ft_strncmp(builtin, "export", ft_strlen("export") + 1) == 0)
		return (builtin_export(cmd->argv, cmd->shell_env));
	else
		return (EXIT_FAILURE);
}
