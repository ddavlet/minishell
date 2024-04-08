#include "execution.h"

int	is_first_operant(t_cmd2 *cmd)
{
    t_oper2 operation;

	cmd_check(cmd);
    operation = cmd->execution->operation;
	if (operation == AND_ || operation == OR_)
		return (1);
	return (0);
}

int	is_second_operant(t_cmd2 *cmd)
{
	t_cmd2	*prev;

	cmd_check(cmd);
	prev = get_previous_cmd(cmd);
	if (prev && (prev->execution->operation == AND_ || prev->execution->operation == OR_))
		return (1);
	return (0);
}

int	is_logic_operation(t_cmd2 *cmd)
{
	cmd_check(cmd);
	if (is_first_operant(cmd) || is_second_operant(cmd))
		return (1);
	return (0);
}

void	evaluate_logic_operation(t_cmd2 *cmd)
{
	int		exit_status;
	t_oper2	operation;

	cmd_check(cmd);
	operation = cmd->execution->operation;
	exit_status = cmd->execution->exit_status;
	if (is_first_operant(cmd) && (operation == OR_
			&& exit_status == EXIT_SUCCESS))
		terminate(cmd, EXIT_SUCCESS, "logical OR success");
	else if (is_first_operant(cmd) && (operation == AND_
			&& exit_status == EXIT_FAILURE))
		terminate(cmd, EXIT_FAILURE, "logical AND failure");
	if (is_second_operant(cmd) && (operation == OR_
			&& exit_status == EXIT_FAILURE))
		terminate(cmd, EXIT_FAILURE, "logical OR failure");
	else if (is_second_operant(cmd) && (operation == AND_
			&& exit_status == EXIT_FAILURE))
		terminate(cmd, EXIT_FAILURE, "logical AND failure");
}
