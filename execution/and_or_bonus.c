#include "execution.h"

static int	is_first_operant(t_executor *exec)
{
	t_cmd	*executed_cmd;
	t_cmd	*next_cmd;

	executed_cmd = current_cmd_in_execution(exec);
	next_cmd = last_cmd_in_execution(exec);
	if (connected_through_operation(executed_cmd, next_cmd)
		&& (next_cmd->operat == AND || next_cmd->operat == OR))
		return (1);
	return (0);
}

static int	is_second_operant(t_executor *exec)
{
	t_cmd	*executed_cmd;
	t_cmd	*previous_cmd;

	executed_cmd = current_cmd_in_execution(exec);
	previous_cmd = last_cmd_in_execution(exec);
	if (connected_through_operation(executed_cmd, previous_cmd)
		&& (previous_cmd->operat == AND || previous_cmd->operat == OR))
		return (1);
	return (0);
}

static void	evaluate_as_first_operant(t_executor *exec)
{
	t_cmd	*executed_cmd;
	int		executed_status;

	executed_cmd = current_cmd_in_execution(exec);
	executed_status = exec->status;
	if (executed_cmd->operat == OR && executed_status == EXIT_SUCCESS)
		terminate(NULL, NULL, EXIT_SUCCESS);
	if (executed_cmd->operat == AND && executed_status == EXIT_FAILURE)
		terminate(NULL, NULL, EXIT_FAILURE);
}

static void evaluate_as_second_operant(t_executor *exec)
{
	t_cmd	*executed_cmd;
	int		executed_status;

	executed_cmd = current_cmd_in_execution(exec);
	executed_status = exec->status;
	if (executed_status == EXIT_FAILURE)
		terminate(NULL, NULL, EXIT_FAILURE);
}

void	evaluate_and_or(t_executor *exec)
{
	t_cmd	*executed_cmd;
	t_cmd	*previous_cmd;
	t_cmd	*next_cmd;

	if (!exec || !exec->cmds)
		terminate(NULL, NULL, EXIT_FAILURE);
	executed_cmd = current_cmd_in_execution(exec);
	next_cmd = next_cmd_in_execution(exec);
	previous_cmd = last_cmd_in_execution(exec);
	if (is_first_operant(exec))
		evaluate_as_first_operant(exec);
	if (is_second_operant(exec))
		evaluate_as_second_operant(exec);
}
