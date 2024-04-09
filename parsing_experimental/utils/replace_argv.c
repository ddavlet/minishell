#include "../parsing2.h"

int	replace_argv(t_cmd2 *cmd, const char **argv_new)
{
	t_execution *execution_new;

	if (!cmd || !argv_new)
		return (-1);
	execution_new = initialize_execution_data();
	if (!execution_new)
		return (-1);
	execution_new->argv = argv_new;
	execution_new->exit_status = cmd->execution->exit_status;
	execution_new->operation = cmd->execution->operation;
	execution_new->pid = cmd->execution->pid;
	execution_new->pipe = cmd->execution->pipe;
	execution_new->redirections = cmd->execution->redirections;
	execution_new->shell_env = cmd->execution->shell_env;
	free_argv(cmd->execution->argv);
    free(cmd->execution);
	cmd->execution = execution_new;
    return (0);
}