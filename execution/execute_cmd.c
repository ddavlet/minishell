#include "execution.h"

static int	handle_cmd_execution(t_executor *exec, t_scope *scope)
{
	char	**argv;
	char	**envp;
	char	*path;

	argv = exec->cmds[exec->command_index]->argv;
	envp = exec->cmds[exec->command_index]->env->envp;
	path = get_path(argv[0], envp);
	if (path == NULL)
	{
		ft_putendl_fd("minishell: execution can't find path", 2);
		terminate(NULL, NULL, EXIT_FAILURE);
	}
	if (manage_input_output(exec, scope) == -1)
	{
		ft_putendl_fd("minishell: execution unable to assign input/output", 2);
		terminate(NULL, NULL, EXIT_FAILURE);
	}

    printf("DEBUG::execve: %s\n", argv[1]);
    ft_printf("DEBUG::pipe_fd[0]: %d\n", scope->pipe->read->fd);
    ft_printf("DEBUG::pipe_fd[1]: %d\n", scope->pipe->write->fd);
	if (execve(path, argv, envp) == -1)
	{
		ft_putendl_fd("minishell: execution failed", 2);
		terminate(NULL, NULL, EXIT_FAILURE);
	}
	return (0);
}

int	execute_cmd(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE);
	scope->pid = fork();
	if (scope->pid == -1)
		terminate(NULL, scope, EXIT_FAILURE);
	if (scope->pid == 0)
		handle_cmd_execution(exec, scope);
	else
		check_exit_value(exec, scope);
}
