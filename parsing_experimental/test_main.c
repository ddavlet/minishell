#include "stdio.h"
#include "parsing2.h"

int main(void)
{
    const char  *line = "export a''rg'=''ech''o '2'";
    t_cmd2      *cmds = parse_command_line(line);

    while (cmds)
    {
        int i = -1;
        while (cmds->argv[++i])
            printf("argv[%d]: '%s'\n", i, cmds->argv[i]);
        t_redir *redir = cmds->redirections;
        while (redir)
        {
            printf("redir name: '%s'\n", redir->redir_name);
            redir = redir->next;
        }
        if (cmds->operation == NOTHING)
            printf("operation: %s\n", "NOTHING");
        else if (cmds->operation == PIPE)
            printf("operation: %s\n", "PIPE");
        else if (cmds->operation == AND)
            printf("operation: %s\n", "AND");
        else if (cmds->operation == OR)
            printf("operation: %s\n", "OR");

        cmds = cmds->next;
    }
}

// int main(void)
// {
//     t_token     *tokens = tokenizer(line);
//     while (tokens)
//     {
//         printf("literal: '%s'\n", tokens->literal);
//         tokens = tokens->next;
//     }
// }