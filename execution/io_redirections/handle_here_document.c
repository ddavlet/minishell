#include "../execution.h"

char    *get_all_variables(const char *line, t_env shell_env)
{
    return (ft_strdup("**placeholder line with variables**"));
}

t_fd_state  *here_document(const char *delimiter, t_env *env)
{
    const char    *line;
    t_pipe  *pipe;
    char    *tmp;

    pipe = create_pipe();
    line = readline("heredoc> ");
    while ((line ) != NULL)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0 && line[ft_strlen(line)] == '\0')
            break;
        tmp = get_all_variables(line, env);
        free(line);
        line = tmp;
        write(pipe->write->fd, line, ft_strlen(line));
        write(pipe->write->fd, "\n", 1);
        free(line);
        line = readline("heredoc> ");
    }
    free(line);
    close_fd(pipe->write);
    return (pipe->read);
}

