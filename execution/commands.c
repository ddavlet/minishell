#include "execution.h"

t_cmd	*get_current_cmd(t_executor *exec)
{
	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"get_current_cmd: missing or incomplete exec");
	return (exec->cmds[exec->command_index]);
}

t_cmd	*get_next_cmd(t_executor *exec, t_cmd *cmd)
{
	int	i;

	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE, "get_next_cmd: missing or incomplete exec");
	i = 0;
	if (cmd == NULL)
		return (NULL);
	while (exec->cmds[i] != cmd && exec->cmds[i + 1] != NULL)
		i++;
	return (exec->cmds[i + 1]);
}

t_cmd	*get_previous_cmd(t_executor *exec, t_cmd *cmd)
{
	int	i;

	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"get_previous_cmd: missing or incomplete exec");
	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (exec->command_index == 0)
		return (NULL);
	while (exec->cmds[i] != cmd && exec->cmds[i + 1] != NULL)
		i++;
	return (exec->cmds[i - 1]);
}