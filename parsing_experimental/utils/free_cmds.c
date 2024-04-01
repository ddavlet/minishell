#include "../parsing2.h"

void    free_cmds(t_cmd2 *cmds)
{
    t_cmd2 *tmp;

    while (cmds->next)
    {
        tmp = cmds->next; 
        free_argv((char **)cmds->argv);
        free_redirections(cmds->redirections);
        free(cmds);
        cmds = tmp;
    }
}