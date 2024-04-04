#include "execution.h"

void    reset_input_output(int stdin, int stdout)
{
        if (dup2(stdin, STDIN_FILENO) == -1)
            ft_putendl_fd("minishell: failed to reset stdin", STDERR_FILENO);
        if (dup2(stdout, STDOUT_FILENO) == -1)
            ft_putendl_fd("minishell: failed to reset stdout", STDERR_FILENO);
}

int	execution(t_cmd2 *cmds)
{
    int		stdin;
    int		stdout;
    t_cmd2  *current_cmd;

    cmds_check(cmds);
    stdin = dup(STDIN_FILENO);
    stdout = dup(STDOUT_FILENO);
    current_cmd = cmds;
	while (current_cmd)
    {
        set_input_output(current_cmd, cmds);
        if (is_builtin(current_cmd))
            current_cmd->exit_status = builtin_router(current_cmd);
        else if (execute_cmd(current_cmd) == -1)
		{
			ft_putendl_fd("failed to execute command", STDERR_FILENO);
			return (-1);
		}
        if (current_cmd->next == NULL || is_and_or(current_cmd, cmds))
            wait_check(current_cmd, cmds);
        reset_input_output(stdin, stdout);
        current_cmd = current_cmd->next;
    }
	return (0);
}
