#include "execution.h"

int	execute_builtin(t_executor *exec)
{
    char    *builtin;
    t_cmd   *cmd;

    set_io_streams(exec);
    cmd = current_cmd(exec);
    builtin = cmd->argv[0];
    if (ft_strncmp(builtin, "cd", ft_strlen("cd")) == 0)
        builtin_cd(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "echo", ft_strlen("echo")) == 0)
        builtin_echo(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "env", ft_strlen("env")) == 0)
        builtin_env(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "exit", ft_strlen("exit")) == 0)
        builtin_exit(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "pwd", ft_strlen("pwd")) == 0)
        builtin_pwd(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "unset", ft_strlen("unset")) == 0)
        builtin_unset(cmd->argv, cmd->env);
    else
        terminate(NULL, EXIT_FAILURE, "minishell: not a builtin");
    exec->command_index++;
    return (0);
}
