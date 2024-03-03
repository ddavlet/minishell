#include "execution.h"

static int	manage_output_redir(t_executor *exec, t_context *context)
{
    t_cmd   *cmd;

    cmd = exec->cmds[exec->command_index];
	if (cmd->redirs != NULL)
	{
		if (context->output_fd != STDOUT_FILENO)
			close(context->output_fd);
		context->output_fd = last_output_redir(exec);
		if (context->output_fd == -1)
			return (-1);
	}
	ft_printf("out_fd: %d\n", context->output_fd);
	dup2(context->output_fd, STDOUT_FILENO);
	if (context->output_fd != STDOUT_FILENO)
		close(context->output_fd);
	return (0);
}

static int	manage_input_redir(t_executor *exec, t_context *context)
{
    t_cmd   *cmd;

    cmd = exec->cmds[exec->command_index];
	if (cmd->redirs != NULL)
	{
		if (context->input_fd != STDIN_FILENO)
			close(context->input_fd);
		context->input_fd = last_input_redir(exec, context);
		if (context->input_fd == -1)
			return (-1);
	}
	ft_printf("in_fd: %d\n", context->input_fd);
	dup2(context->input_fd, STDIN_FILENO);
	if (context->input_fd != STDIN_FILENO)
		close(context->input_fd);
	return (0);
}

int	cmd_process(t_executor *exec, t_context *context)
{
    char    **argv;
    char    **envp;
    t_cmd   *cmd;
    
    if (!exec || !exec->cmds || !exec->cmds[exec->command_index])
    {
        terminate(NULL, NULL, EXIT_FAILURE);
    }
	cmd = exec->cmds[exec->command_index];
    if (cmd->operat == PIPE)
		dup2(context->pipe->write->fd, STDOUT_FILENO);
	manage_output_redir(exec, context);
	manage_input_redir(exec, context);
    if (cmd->operat == PIPE)
        close(context->pipe->write->fd);
    argv = exec->cmds[exec->command_index]->argv;
    envp = exec->cmds[exec->command_index]->env->envp;
	execute_cmd(argv, envp);
	return (0);
}

    // ft_printf("DEBUG::cmd\n");
    // ft_printf("DEBUG::pipe_fd[0]: %d\n", exec->pipe_fd[0]);
    // ft_printf("DEBUG::pipe_fd[1]: %d\n", exec->pipe_fd[1]);