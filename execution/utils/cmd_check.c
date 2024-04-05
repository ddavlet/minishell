#include "../execution.h"

void	cmd_check(t_cmd2 *cmd)
{
	if (!cmd)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing command");
	if (!cmd->execution)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing execution");
	if (!cmd->execution->argv)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing argv");
	if (!cmd->execution->pipe)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing pipe");
	if (!cmd->execution->shell_env)
		terminate(cmd, EXIT_FAILURE,
			"failed command check: missing shell environment");
	if (!cmd->execution->redirections)
		terminatwe(cmd, EXIT_FAILURE,
			"failed command check: missing redirections");
}
