#include "execution.h"

void	wait_until(t_cmd2 *cmd)
{
    t_cmd2  *last;
	int		exit_status;
	pid_t	pid;

    cmd_check(cmd);
    last = cmd->cmds;
	while (last && last->execution->exit_status == EXIT_SUCCESS)
	{
        cmd_check(last);
        last = last->next;
    }
	while (last != cmd->next)
	{
        if (is_builtin(last))
            last = last->next;
        else
        {
            pid = last->execution->pid;
            waitpid(pid, &exit_status, 0);
            last->execution->exit_status = exit_status;
            last = last->next;
        }
	}
}

int	wait_check(t_cmd2 *cmd)
{
	cmd_check(cmd);
    if (cmd->next == NULL)
        wait_until(cmd);
    else if (is_logic_operation(cmd))
    {
        wait_until(cmd);
		evaluate_logic_operation(cmd);
    }
	return (0);
}
