#include "execution.h"

int	is_first_operant(t_executor *exec, t_cmd *cmd)
{
	t_cmd	*next;

	next = next_cmd(exec, cmd);
	if (connected_through_operation(cmd, next) && cmd->operat != PIPE)
		return (1);
	return (0);
}

int	is_second_operant(t_executor *exec, t_cmd *cmd)
{
	t_cmd	*prev;

	prev = previous_cmd(exec, cmd);
	if (connected_through_operation(cmd, prev) && prev->operat != PIPE)
		return (1);
	return (0);
}

int	is_logic(t_executor *exec)
{
	t_cmd	*cmd;

	cmd = current_cmd(exec);
	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"is_final: missing or incomplete exec");
	if (has_nested_scope(cmd))
		cmd = final_cmd_in_scope(exec, get_nested_scope(cmd));
	if (is_first_operant(exec, cmd) || is_second_operant(exec, cmd))
		return (1);
	return (0);
}

void	evaluate_logic_operator(t_executor *exec)
{
    t_cmd *cmd;
	int	executed_status;

	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE, NULL);
    cmd = current_cmd(exec);
	executed_status = exec->status_codes[exec->command_index];
	if (is_first_operant(exec, cmd) && (cmd->operat == OR
			&& executed_status == EXIT_SUCCESS))
		terminate(NULL, EXIT_SUCCESS, "logical OR success");
	else if (is_first_operant(exec, cmd) && (cmd->operat == AND
			&& executed_status == EXIT_FAILURE))
		terminate(NULL, EXIT_SUCCESS, "logical AND failure");
	if (is_second_operant(exec, cmd) && (cmd->operat == OR
			&& executed_status == EXIT_FAILURE))
		terminate(NULL, EXIT_SUCCESS, "logical OR failure");
	else if (is_second_operant(exec, cmd) && (cmd->operat == AND
			&& executed_status == EXIT_FAILURE))
		terminate(NULL, EXIT_SUCCESS, "logical AND failure");
}
