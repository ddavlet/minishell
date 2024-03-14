#include "execution.h"

int	check_exit_value(t_executor *exec)
{
	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE, "parameter check failed");
	if (is_logic(exec))
	{
		waitpid(exec->pid, &(exec->status), 0);
		evaluate_logic_operator(exec);
	}
	else if (is_final(exec))
        waitpid(exec->pid, &(exec->status), 0);
	return (0);
}
