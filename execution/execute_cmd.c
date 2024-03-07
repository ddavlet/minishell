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
		terminate(NULL, NULL, EXIT_FAILURE,
			"minishell: execution can't find path");
	if (manage_input_output(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE,
			"minishell: execution unable to assign input/output");
	// ft_putstr_fd("DEBUG::pipe->read: ", 2);
	// ft_putendl_fd(ft_itoa(scope->pipe->read->fd), 2);
	// ft_putstr_fd("DEBUG::pipe->write: ", 2);
	// ft_putendl_fd(ft_itoa(scope->pipe->write->fd), 2);
	ft_putstr_fd("DEBUG::execve: ", 2);
	ft_putendl_fd(argv[0], 2);
	ft_putstr_fd("DEBUG::path: ", 2);
	ft_putendl_fd(path, 2);
    if (execve(path, argv, envp) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "minishell: execution failed");
	return (0);
}

int	execute_cmd(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "param check");
    scope->pipe = create_pipe();
	if (scope->pipe == NULL)
		terminate(NULL, NULL, EXIT_FAILURE,
			"couldn't create pipe");
	scope->pid = fork();
	if (scope->pid == -1)
		terminate(NULL, scope, EXIT_FAILURE, NULL);
	if (scope->pid == 0)
		handle_cmd_execution(exec, scope);
	else
    {
        manage_pipe(exec, scope);
		check_exit_value(exec, scope);
    }
}

void    manage_pipe(t_executor *exec, t_scope *scope)
{
    if (in_fd != STDIN_FILENO)
            close(in_fd);
    in_fd = pipe_fd[0];
    close(pipe_fd[1]);
    if (cmds[cmd_index + 1] == NULL)
    {
        waitpid(pid, &status, 0);
                close(in_fd);
    }
}