#include "execution.h"

void reset_input_output(int stdin, int stdout)
{
	if (dup2(stdin, STDIN_FILENO) == -1)
		ft_putendl_fd("minishell: failed to reset stdin", STDERR_FILENO);
	if (dup2(stdout, STDOUT_FILENO) == -1)
		ft_putendl_fd("minishell: failed to reset stdout", STDERR_FILENO);
}

void	execution(t_cmd2 *cmds)
{
	int stdin;
	int stdout;
	t_cmd2 *cmd;

	if (!cmds)
		return ;
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	cmd = cmds;
	configure_signals_execution();
	while (cmd && cmd->execution->argv[0] && cmd->execution->argv[0][0])
	{
		set_input_output(cmd);
		expand_variables(cmd, cmds->execution->shell_env);
		if (is_builtin(cmd) && !is_piped(cmd))
			builtin_router(cmd);
		else
			if (execute_cmd(cmd))
				return ;
		if (cmd->next == NULL || is_logic_operation(cmd))
			if (wait_check(cmd))
				break ;
		reset_input_output(stdin, stdout);
		cmd = cmd->next;
	}
	free_cmds(cmds);
}
