#include "../execution.h"

int handle_here_document(const char *delimiter, t_executor *executor)
{
    char    *line;
    
    line = readline("> ");
    while ((line ) != NULL)
    {
        if (strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
            break;
        write(executor->pipe_fd[1], line, strlen(line));
        write(executor->pipe_fd[1], "\n", 1);
        free(line);
        line = readline("> ");
    }
    free(line);
    return (executor->pipe_fd[0]);
}
