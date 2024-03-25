#include "../execution.h"

t_fd_state  *here_document(t_executor *exec, const char *delimiter)
{
    char    *line;
    t_pipe  *pipe;
    char    *tmp;
    t_env   env;
    (void)env;
    (void)tmp;
    (void)exec;

    pipe = create_pipe();
    line = readline("heredoc> ");
    while ((line ) != NULL)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0 && line[ft_strlen(line)] == '\0')
            break;
        // tmp = get_envvar(line, env);
        // free(line);
        // line = tmp;
        // ft_printf("line: %s\n", line);
        write(pipe->write->fd, line, ft_strlen(line));
        write(pipe->write->fd, "\n", 1);
        free(line);
        line = readline("heredoc> ");
    }
    free(line);
    close_fd(exec, pipe->write);
    return (pipe->read);
}

