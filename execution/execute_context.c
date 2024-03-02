#include "execution.h"

static int	has_finished_context(t_executor *exec, t_context *context)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;

	current_cmd = exec->cmds[exec->command_index];
	next_cmd = exec->cmds[exec->command_index + 1];
	if (next_cmd == NULL
		|| next_cmd->context_depth < current_cmd->context_depth)
		return (1);
	return (0);
}

static int	check_execution_status(t_executor *exec, t_context *content)
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

static int	prepare_next(t_executor *exec, t_context *context)
{
	if (!exec || !context)
		return (-1);
	ft_printf("DEBUG::prepare_next\n");
	close_file_descriptors(exec, context);
	check_execution_status(exec, context);
	return (0);
}

int	execute_context(t_executor *exec, t_context *context)
{
	while (!has_finished_context(exec, context))
	{
		if (is_buildin(exec))
			exec->signal = BUILTIN;
		else
		{
			context->pid = fork();
			if (context->pid == -1)
				terminate(NULL, context, EXIT_FAILURE);
			if (context->pid == 0)
				exit(cmd(exec, context));
			else
				prepare_next(exec, context);
		}
	}
	terminate(NULL, context, EXIT_SUCCESS);
}

// ft_printf("DEBUG:loop.c: pipe_fd[0]: %d\n", exec->pipe_fd[0]);
// ft_printf("DEBUG:loop.c: pipe_fd[1]: %d\n", exec->pipe_fd[1]);