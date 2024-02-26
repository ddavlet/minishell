#include "execution.h"

static int	manage_output_redir(t_executor *exec, int cmd_index)
{
	if (exec->cmds[cmd_index + 1] != NULL)
	{
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
	}
	if (exec->cmds[cmd_index]->redirs != NULL)
	{
		if (exec->out_fd != STDOUT_FILENO)
			close(exec->out_fd);
		exec->out_fd = find_last_output_redir(exec, cmd_index);
		if (exec->out_fd == -1)
			return (-1);
	}
	ft_printf("out_fd: %d\n", exec->out_fd);
	dup2(exec->out_fd, STDOUT_FILENO);
	if (exec->out_fd != STDOUT_FILENO)
		close(exec->out_fd);
	return (0);
}

static int	manage_input_redir(t_executor *exec, int cmd_index)
{
	if (exec->cmds[cmd_index]->redirs != NULL)
	{
		if (exec->in_fd != STDIN_FILENO)
			close(exec->in_fd);
		exec->in_fd = find_last_input_redir(exec, cmd_index);
		if (exec->in_fd == -1)
			return (-1);
	}
	ft_printf("in_fd: %d\n", exec->in_fd);
	dup2(exec->in_fd, STDIN_FILENO);
	if (exec->in_fd != STDIN_FILENO)
		close(exec->in_fd);
	return (0);
}

int	child_process(t_executor *exec, int cmd_index)
{
    char    **argv;
    char    **envp;

    if (!exec || !exec->cmds || !exec->cmds[cmd_index])
        return (-1);
	manage_output_redir(exec, cmd_index);
	manage_input_redir(exec, cmd_index);
    close(exec->pipe_fd[1]);
    argv = exec->cmds[cmd_index]->argv;
    envp = exec->cmds[cmd_index]->env->envp;
	execute_command(argv, envp);
	return (0);
}

void    configure_execution(t_executor *exec, int cmd_index)
{
}

    // ft_printf("DEBUG::child_process\n");
    // ft_printf("DEBUG::pipe_fd[0]: %d\n", exec->pipe_fd[0]);
    // ft_printf("DEBUG::pipe_fd[1]: %d\n", exec->pipe_fd[1]);