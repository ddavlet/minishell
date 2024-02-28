#include "execution.h"

int	setup_pipe(t_executor *exec, t_context *context)
{
	if (exec->cmds[exec->command_index]->operat != PIPE)
		return (0);
	if (pipe(context->pipe->pipe_fd) == -1)
	{
        // Protect with exit
		perror("pipe");
		return (-1);
	}
	return (0);
}

static int	check_child_status(t_executor *exec, t_context *content)
{
	/*
		if (WIFEXITED(exec->status))
		{
			if (WEXITSTATUS(exec->status) == 0)
				return (0);
			else
				return (1);
		}
		else if (WIFSIGNALED(exec->status))
		{
			if (WTERMSIG(exec->status) == SIGINT)
				return (130);
			else if (WTERMSIG(exec->status) == SIGQUIT)
				return (131);
			else
				return (128 + WTERMSIG(exec->status));
		}
	*/
	ft_printf("DEBUG::parent.c: exec->status: %d\n", content->status);   
	if (content->status != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putendl_fd(strerror(content->status), 2);
		return (-1);
	}
	return (0);
}

static int	close_file_descriptors(t_executor *exec, t_context *context)
{
	if (!exec || !exec->cmds)
		return (-1);
	if (context->input_fd != 0)
		close(context->input_fd);
	context->input_fd = pipe_fd[0];
	close(exec->pipe_fd[1]);
	if (exec->cmds[cmd_index + 1] == NULL)
	{
		waitpid(exec->pid, &(exec->status), 0);
		close(context->input_fd);
	}
	return (0);
}

static int	prepare_next_execution(t_executor *exec, t_context *context)
{
	if (!exec || !context)
		return (-1);
	ft_printf("DEBUG::prepare_next_execution\n");
	close_file_descriptors(exec, context);
	check_child_status(exec, context);
	return (0);
}
 
int execute_context(t_executor *exec, t_context *context)
{
    setup_pipe(exec, context);
    while (!context_has_terminated(context))
    {
		context->pid = fork();
		if (context->pid == -1)
			return (-1); // Protect with exit handler
		if (context->pid == 0)
            exit(child_process(exec, context));
		else
            prepare_next_execution(exec, context);
    }
}


		// ft_printf("DEBUG:loop.c: pipe_fd[0]: %d\n", exec->pipe_fd[0]);
		// ft_printf("DEBUG:loop.c: pipe_fd[1]: %d\n", exec->pipe_fd[1]);