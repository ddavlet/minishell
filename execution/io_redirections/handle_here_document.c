#include "../execution.h"

int handle_here_document(const char *delimiter, t_env *env, t_context *context)
{
    char    *line;
    char    *tmp;

    (void)env;
    (void)tmp;
    line = readline("heredoc> ");
    while ((line ) != NULL)
    {
        if (strncmp(line, delimiter, ft_strlen(line)) == 0 && line[ft_strlen(line)] == '\0')
            break;
        // tmp = get_envvar(line, env);
        // free(line);
        // line = tmp;
        // ft_printf("line: %s\n", line);
        write(context->pipe->write->fd, line, strlen(line));
        write(context->pipe->write->fd, "\n", 1);
        free(line);
        line = readline("heredoc> ");
    }
    free(line);
    return (context->pipe->read->fd);
}
