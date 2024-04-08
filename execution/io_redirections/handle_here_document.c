#include "../execution.h"

t_fd_state  *here_document(const char *delimiter, t_env *shell_env)
{
    const char    *line;
    t_pipe  *pipe;
    const char    *tmp;

    pipe = create_pipe();
    line = (const char *)readline("heredoc> ");
    while ((line ) != NULL)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0 && line[ft_strlen(line)] == '\0')
            break;
        tmp = replace_variables(line, shell_env);
        free((void *)line);
        line = tmp;
        write(pipe->write->fd, line, ft_strlen(line));
        write(pipe->write->fd, "\n", 1);
        free((void *)line);
        line = (const char *)readline("heredoc> ");
    }
    free((void *)line);
    close_fd(pipe->write);
    return (pipe->read);
}

