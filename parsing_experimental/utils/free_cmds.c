#include "../parsing2.h"

void    free_execution_data(t_execution *execution)
{
    if (execution)
    {
        if (execution->argv)
            free_argv(execution->argv);
        if (execution->pipe)
            free_pipe(execution->pipe);
        if (execution->redirections)
            free_redirections(execution->redirections);
        free(execution);
    }
}

void    free_cmds(t_cmd2 *cmds)
{
    t_cmd2  *tmp;
    t_cmd2  *cmd;

    cmd = cmds;
    while (cmds)
    {
        tmp = cmd->next; 
        free_execution_data(cmd->execution);
        free(cmd);
        cmd = tmp->next;
    }
}