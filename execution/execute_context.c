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

static int	prepare_next(t_executor *exec, t_context *context)
{
	if (!exec || !context)
		return (-1);
	waitpid(context->pid, &(exec->status), 0);
	if (exec->status != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putendl_fd(strerror(exec->status), 2);
		return (-1);
	}
	exec->command_index++;
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
				exit(cmd_process(exec, context));
			else if (prepare_next(exec, context) == -1)
				break;
		}
	}
	terminate(NULL, context, exec->status);
}

// ft_printf("DEBUG:loop.c: pipe_fd[0]: %d\n", exec->pipe_fd[0]);
// ft_printf("DEBUG:loop.c: pipe_fd[1]: %d\n", exec->pipe_fd[1]);


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

