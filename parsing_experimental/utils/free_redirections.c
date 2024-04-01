#include "../parsing2.h"

void    free_redirections(t_redir *redirs)
{
    t_redir *tmp;

    while (redirs->next)
    {
        tmp = redirs->next;
        free(redirs->redir_name);
        free(redirs);
        redirs = tmp;
    }
}