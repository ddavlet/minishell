#include "../execution.h"

int handle_here_document(const char *delimiter, t_env *env, t_executor *executor)
{
    char    *line;
    char    *tmp;

    (void)env;
    (void)tmp;
    line = readline("> ");
    while ((line ) != NULL)
    {
        if (strncmp(line, delimiter, ft_strlen(line)) == 0 && line[ft_strlen(line)] == '\0')
            break;
        // tmp = get_envvar(line, env);
        // free(line);
        // line = tmp;
        // ft_printf("line: %s\n", line);
        write(executor->pipe_fd[1], line, strlen(line));
        write(executor->pipe_fd[1], "\n", 1);
        free(line);
        line = readline("> ");
    }
    free(line);
    return (executor->pipe_fd[0]);
}
