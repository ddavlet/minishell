#include "stdio.h"
#include "parsing2.h"

int main(void)
{
    // const char  *line = "export a\"\"rg\"=\"\"'\"echo\"'\"\" \"2 && (pwd | cat <infile)";
    const char  *line = "export arg='echo2' && ( pwd | cat <infile )";

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
        if (cmds->operation == NONE)
            printf("operation: %s\n", "NONE");
        else if (cmds->operation == PIPE_)
            printf("operation: %s\n", "PIPE");
        else if (cmds->operation == AND_)
            printf("operation: %s\n", "AND");
        else if (cmds->operation == OR_)
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