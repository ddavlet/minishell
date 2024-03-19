#include "execution.h"

static t_executor	*initialize_executor(t_cmd **cmds, char **envp)
{
	t_executor	*exec;

	if (!cmds || !envp)
		return (NULL);
	exec = (t_executor *)ft_calloc(1, sizeof(t_executor));
	if (!exec)
		return (NULL);
	exec->cmds = cmds;
	exec->envp = envp;
	exec->command_index = 0;
	exec->status = 0;
	exec->pipes = initialize_pipes(exec);
	if (!exec->pipes)
	{
		terminate(exec, EXIT_FAILURE, "minishell: failed to initialize pipes");
	}
	return (exec);
}

void	prepare_next(t_executor *exec)
{
    t_cmd   *cmd;
	t_cmd	*prev;

    cmd = current_cmd(exec);
    if (next_cmd(exec, cmd) == NULL)
    {
        return ;
    }
	prev = previous_cmd(exec, current_cmd(exec));
	if (has_nested_scope(prev))
		prev = first_cmd_in_scope(exec, get_nested_scope(prev));
	if (prev->operat == PIPE)
        close_next_pipe(exec);

}

static void	execute_nested_scope(t_executor *exec)
{
	char	**argv;
	char	**envp;
	t_cmd	**scope_ptr;
	int		scope_len;

	scope_ptr = exec->cmds + exec->command_index;
	scope_len = scope_length(exec, current_cmd(exec),
			get_nested_scope(current_cmd(exec)));
	argv = reverse_pars(scope_ptr, scope_len);
	envp = exec->envp;
	exec->pid = fork();
	if (exec->pid == -1)
		terminate(exec, EXIT_FAILURE, "failed to fork");
	else if (exec->pid == 0)
	{
		set_io_streams(exec);
		execute(argv, envp);
	}
	else if (is_final(exec) || is_logic(exec))
		check_exit_value(exec);
	skip_nested_cmds(exec);
}

static void	execute_cmd(t_executor *exec)
{

	char	**argv;
	char	**envp;

	envp = exec->envp;
	argv = current_cmd(exec)->argv;
	exec->pid = fork();
	if (exec->pid == -1)
		terminate(exec, EXIT_FAILURE, "failed to fork");
	else if (exec->pid == 0)
	{
		set_io_streams(exec);
		execute(argv, envp);
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
		if (has_nested_scope(current_cmd(exec)))
			execute_nested_scope(exec);
		else if (is_builtin(exec))
			execute_builtin(exec);
		else
			execute_cmd(exec);
        prepare_next(exec);
	}
	return (0);
}
