#include "execution.h"

static t_executor	*initialize_executor(t_cmd **cmds, char **envp)
{
	t_executor	*exec;

	if (!cmds || !envp)
		return (NULL);
	exec = (t_executor *)ft_calloc(1, sizeof(t_executor));
	if (!exec)
		return (NULL);
	exec->envp = envp;
	exec->command_index = 0;
	exec->cmds = cmds;
	exec->status = 0;
	return (exec);
}

void	skip_nested_cmds(t_executor *exec)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*next;

	i = 1;
	cmd = current_cmd(exec);
	next = next_cmd(exec, cmd);
	while (is_inside_scope(next, get_nested_scope(exec)))
	{
		cmd = next;
		next = next_cmd(exec, cmd);
		i++;
	}
	exec->command_index += i;
}

static void	execute_nested_scope(t_executor *exec)
{
	char	**argv;

	exec->pid = fork();
	if (exec->pid == -1)
		terminate(exec, EXIT_FAILURE, "failed to fork");
	else if (exec->pid == 0)
	{
		set_io_streams(exec);
		argv = reverse_pars(exec->cmds + exec->command_index, scope_length(exec,
					get_nested_scope(exec)));
		execute(argv, envp(exec));
	}
	else if (is_final(exec) || is_logic(exec))
		check_exit_value(exec);
	skip_nested_cmds(exec);
}

static void	execute_cmd(t_executor *exec)
{
	exec->pid = fork();
	if (exec->pid == -1)
		terminate(exec, EXIT_FAILURE, "failed to fork");
	else if (exec->pid == 0)
	{
		set_io_streams(exec);
		execute(argv(exec), envp(exec));
	}
	else if (is_final(exec) || is_logic(exec))
		check_exit_value(exec);
	exec->command_index++;
}

int	execution(t_cmd **cmds, char **envp)
{
	t_executor	*exec;

	if (!cmds)
		terminate(NULL, EXIT_FAILURE, NULL);
	if (cmds[0] == NULL)
		terminate(NULL, EXIT_SUCCESS, NULL);
	exec = initialize_executor(cmds, envp);
	if (!exec)
		terminate(NULL, EXIT_FAILURE, "failed to initialize executor");
	while (current_cmd(exec) != NULL)
	{
		if (is_nested_scope(exec))
			execute_nested_scope(exec);
		else if (is_builtin(exec))
			execute_builtin(exec);
		else
			execute_cmd(exec);
	}
	return (0);
}
