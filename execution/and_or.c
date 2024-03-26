#include "execution.h"

int	is_first_operant(t_executor *exec, t_cmd *cmd)
{
	t_cmd	*next;

	next = get_next_cmd(exec, cmd);
	if (cmd->operat == AND || cmd->operat == OR)
		return (1);
	return (0);
}

int	is_second_operant(t_executor *exec, t_cmd *cmd)
{
	t_cmd	*prev;

	prev = get_previous_cmd(exec, cmd);
	if (cmd->operat == AND || cmd->operat == OR)
		return (1);
	return (0);
}

int	is_logic(t_executor *exec)
{
	t_cmd	*cmd;

	cmd = get_current_cmd(exec);
	if (!exec || !exec->cmds)
		terminate(exec, EXIT_FAILURE,
			"is_final: missing or incomplete exec");
	if (is_first_operant(exec, cmd) || is_second_operant(exec, cmd))
		return (1);
	return (0);
}

void	evaluate_logic_operator(t_executor *exec)
{
    t_cmd *cmd;
	int	exit_code;

	if (!exec || !exec->cmds)
		terminate(exec, EXIT_FAILURE, "failed to evaluate logic");
    cmd = get_current_cmd(exec);
	exit_code = get_exit_code(exec, exec->command_index);
	if (is_first_operant(exec, cmd) && (cmd->operat == OR
			&& exit_code == EXIT_SUCCESS))
		terminate(exec, EXIT_SUCCESS, "logical OR success");
	else if (is_first_operant(exec, cmd) && (cmd->operat == AND
			&& exit_code == EXIT_FAILURE))
		terminate(exec, EXIT_FAILURE, "logical AND failure");
	if (is_second_operant(exec, cmd) && (cmd->operat == OR
			&& exit_code == EXIT_FAILURE))
		terminate(exec, EXIT_FAILURE, "logical OR failure");
	else if (is_second_operant(exec, cmd) && (cmd->operat == AND
			&& exit_code == EXIT_FAILURE))
		terminate(exec, EXIT_FAILURE, "logical AND failure");
}
