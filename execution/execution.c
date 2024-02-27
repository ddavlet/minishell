
#include "execution.h"

t_context   *initialize_context(void)
{
    t_context   *context;

    context = (t_context *)ft_calloc(1, sizeof(t_context));
    if (!context)
        return (NULL);
    context->after = RUN;
    context->before = RUN;
    context->pid = -1;
    context->pipe_fd = NULL;
}

t_executor	*initialize_executor(t_cmd **cmds)
{
	t_executor	*exec;

	if (!cmds)
		return (NULL);
	exec = (t_executor *)calloc(sizeof(t_executor));
	if (!exec)
		return (NULL);
	exec->command_index = 0;
	exec->cmds = cmds;
	exec->in_fd = 0;
	exec->out_fd = 1;
	exec->status = -1;
	return (exec);
}

int	execution(t_cmd **cmds)
{
	t_executor	*exec;
    t_context   *context;

	if (!cmds)
		return (-1);
    if (cmds[0] == NULL)
        return (0);
	exec = initialize_executor(cmds, envp);
	if (!exec)
		return (-1);
    context = initialize_context(exec);
    if (!context)
        handle_exit();
    context->pid = fork();
    if (context->pid == -1)
        handle_exit();
    else if (context->pid == 0)
        execute_rekursively(exec, context);
    else
        waitpid(context->pid, &(exec->status), 0);
	terminate_execution(exec);
	return (0);
}

int    execute_rekursiv(t_executor exec, t_context *context)
{
    t_context   *subcontext;
    t_cmd       *current_cmd;

    subcontext = NULL;
    current_cmd = current_command(exec);
    if (current_cmd->open_parenthesis > 0)
    {
        subcontext = create_subcontext(current_cmd, context);
        subcontext->pid = fork();
        if (subcontext_pid == -1)
            exit_handler();
        if (subcontext_pid == 0)
            exit(execute_rekursiv(exec, subcontext));
        else
            handle_exit_value(exec, subcontext);
    }
    else
        exit(execute_loop(exec, context));
}

void    handle_exit_value(t_executor *exec, t_context *context)
{
    waitpid(subcontext->pid, &(exec->status), 0);
}

void    handle_exit(void)
{
    return ;
}

t_context   *create_subcontext(t_cmd *cmd, t_context *context)
{
    cmd->open_parenthesis -= 1;
    return (NULL);
}


