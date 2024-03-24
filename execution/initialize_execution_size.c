#include "execution.h"

void	initialize_execution_size(t_executor *exec)
{
	int		size;
	t_cmd	*cmd;

	size = 0;
	cmd = current_cmd(exec);
	while (cmd != NULL)
	{
		if (has_nested_scope(cmd))
			cmd = final_cmd_in_scope(exec, get_nested_scope(cmd));
		cmd = next_cmd(exec, cmd);
		size++;
	}
	exec->size = size;
}
