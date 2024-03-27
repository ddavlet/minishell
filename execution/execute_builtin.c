#include "execution.h"

static int	builtin_router(t_cmd *cmd)
{
	char	*builtin;

	builtin = cmd->argv[0];
	if (ft_strncmp(builtin, "cd", ft_strlen("cd") + 1) == 0)
		return (builtin_cd(cmd->argv, cmd->env));
	else if (ft_strncmp(builtin, "echo", ft_strlen("echo") + 1) == 0)
		return (builtin_echo(cmd->argv, cmd->env));
	else if (ft_strncmp(builtin, "env", ft_strlen("env") + 1) == 0)
		return (builtin_env(cmd->argv, cmd->env));
	else if (ft_strncmp(builtin, "exit", ft_strlen("exit") + 1) == 0)
		return (builtin_exit(cmd->argv, cmd->env));
	else if (ft_strncmp(builtin, "pwd", ft_strlen("pwd") + 1) == 0)
		return (builtin_pwd(cmd->argv, cmd->env));
	else if (ft_strncmp(builtin, "unset", ft_strlen("unset") + 1) == 0)
		return (builtin_unset(cmd->argv, cmd->env));
	else if (ft_strncmp(builtin, "export", ft_strlen("export") + 1) == 0)
		return (builtin_export(cmd->argv, cmd->env));
	else
		return (EXIT_FAILURE);
}

void	execute_builtin(t_executor *exec)
{
	int		exit_code;
	t_cmd	*cmd;

	cmd = get_current_cmd(exec);
	exit_code = builtin_router(cmd);
	set_exit_code(exec, exit_code, exec->command_index);
}
