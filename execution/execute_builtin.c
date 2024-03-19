#include "execution.h"

int	execute_builtin(t_executor *exec)
{
    char    *builtin;
    t_cmd   *cmd;

    set_io_streams(exec);
    cmd = current_cmd(exec);
    builtin = cmd->argv[0];
    if (ft_strncmp(builtin, "cd", 2))
        builtin_cd(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "echo", 2))
        builtin_echo(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "env", 2))
        builtin_env(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "exit", 2))
        builtin_exit(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "pwd", 2))
        builtin_pwd(cmd->argv, cmd->env);
    else if (ft_strncmp(builtin, "unset", 2))
        builtin_unset(cmd->argv, cmd->env);
    else
        terminate(NULL, EXIT_FAILURE, "minishell: not a builtin");
    return (0);
}
