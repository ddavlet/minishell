#include "execution.h"

t_cmd2	*get_next_cmd(t_cmd2 *cmd)
{
	t_cmd2	*next;

	if (!cmd || !cmd->cmds)
		terminate(cmd, EXIT_FAILURE, "failed to find command");
	next = cmd->cmds;
	while (next && next != cmd->next)
		next = next->next;
    cmd_check(next);
	return (next);
}

t_cmd2	*get_previous_cmd(t_cmd2 *cmd)
{
	t_cmd2 *prev;

	if (!cmd || !cmd->cmds)
		terminate(cmd, EXIT_FAILURE, "failed to find command");
	if (cmd == cmd->cmds)
		return (NULL);
	prev = cmd->cmds;
	while (prev && prev->next != cmd)
		prev = prev->next;
    cmd_check(prev);
	return (prev);
}