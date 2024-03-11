#include "execution.h"

static int	is_first_operant(t_executor *exec)
{
	if (next_cmd_connected_through_operation(exec)
		&& (next_cmd_in_execution(exec)->operat == AND
			|| next_cmd_in_execution(exec)->operat == OR))
		return (1);
	return (0);
}

static int	is_second_operant(t_executor *exec)
{
	if (previous_cmd_connected_through_operation(exec)
		&& (previous_cmd_in_execution(exec)->operat == AND
			|| previous_cmd_in_execution(exec)->operat == OR))
		return (1);
	return (0);
}

void	evaluate_and_or(t_executor *exec)
{
	int	executed_status;

	if (!exec || !exec->cmds)
		terminate(NULL, NULL, EXIT_FAILURE, NULL);
	executed_status = exec->status;
	if (is_first_operant(exec) && (current_cmd_in_execution(exec)->operat == OR
			&& executed_status == EXIT_SUCCESS))
		terminate(NULL, NULL, EXIT_SUCCESS, "logical OR success");
	else if (is_first_operant(exec)
		&& (current_cmd_in_execution(exec)->operat == AND
			&& executed_status == EXIT_FAILURE))
		terminate(NULL, NULL, EXIT_SUCCESS, "logical AND failure");
	if (is_second_operant(exec) && (current_cmd_in_execution(exec)->operat == OR
			&& executed_status == EXIT_FAILURE))
		terminate(NULL, NULL, EXIT_SUCCESS, "logical OR failure");
	else if (is_second_operant(exec)
		&& (current_cmd_in_execution(exec)->operat == AND
			&& executed_status == EXIT_FAILURE))
		terminate(NULL, NULL, EXIT_SUCCESS, "logical AND failure");
}
