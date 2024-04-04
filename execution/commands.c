#include "execution.h"

t_cmd2	*get_current_cmd(t_executor *exec)
{
	if (!exec || !exec->cmds)
		terminate(exec, EXIT_FAILURE,
			"get_current_cmd: missing or incomplete exec");
	return (exec->cmds[exec->command_index]);
}

t_cmd2	*get_next_cmd(t_executor *exec, t_cmd2 *cmd)
{
    t_cmd2  *next;
	if (!exec || !exec->current_cmd || !exec->first_cmd || !cmd)
		terminate(exec, EXIT_FAILURE, "get_next_cmd: failed to find command");
    next = exec->first_cmd;
	while (next && next != cmd->next)
		next = next->next;
	return (next);
}

t_cmd2	*get_previous_cmd(t_executor *exec, t_cmd2 *cmd)
{
	t_cmd2 *prev;

	if (!exec || !exec->first_cmd || !exec->current_cmd || !cmd)
		terminate(exec, EXIT_FAILURE,
			"get_previous_cmd: missing or incomplete exec");
	if (exec->first_cmd == exec->current_cmd)
		return (NULL);
	prev = exec->first_cmd;
	while (prev && prev->next != cmd)
		prev = prev->next;
	return (prev);
}