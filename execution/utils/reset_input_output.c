#include "../execution.h"

void    reset_input_output(t_executor *exec)
{
        if (dup2(exec->stdin, STDIN_FILENO) == -1)
            terminate(exec, EXIT_FAILURE,
                "minishell: unable to reset stdin");
        if (dup2(exec->stdout, STDOUT_FILENO) == -1)
            terminate(exec, EXIT_FAILURE,
                "minishell: unable to reset stdout");
}