#include "execution.h"

int32_t	scope_depth(int	*scope)
{
	int32_t	i;

	i = -1;
	while (scope[++i])
		;
	return (i);
}

bool	has_scopes(t_exec **execs)
{
	ssize_t	i;
	int32_t	j;

	i = -1;
	j = 1;
	while (execs[++i])
	{
		if (scope_depth(execs[i]->cmd->scope_stack) > 1)
		{

		}
	}
}

ssize_t	numof_commands(t_cmd **cmds)
{
	ssize_t	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

ssize_t	numof_executors(t_exec	**exec)
{
	ssize_t	i;

	i = -1;
	while (exec[++i])
		;
	return (i);
}

t_exec	**init_execs(t_cmd **cmds)
{
	t_exec	**execs;
	ssize_t	i;

	i = 0;
	execs = (t_exec **)ft_calloc(sizeof(t_exec *), numof_commands(cmds) + 1);
	while (cmds[++i])
		execs[i]->cmd;
	return (execs);
}

bool	redir_in(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->redir_sym == HEAR_DOC
			|| tmp->redir_sym == RED_INP)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	redir_out(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->redir_sym == APP_OUT
			|| tmp->redir_sym == RED_OUT)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	set_pipes(t_exec **exec, ssize_t i)
{
	pipe(exec[i]->pipe);
	if (redir_in(exec[i]->cmd->redirs))
		exec[i]->has_redir_in = true;
	if (redir_out(exec[i]->cmd->redirs))
		exec[i]->has_redir_out = true;
	if (i < numof_executors(exec))
		if (exec[i]->cmd->operat == PIPE)
			exec[i]->has_redir_out = true;
	if (i != 0)
		if (exec[i - 1]->cmd->operat == PIPE)
			exec[i]->has_redir_in = true;
}

void	child_exec(t_exec **execs, ssize_t i)
{
	if (execs[i]->has_redir_in == true)
	{
		dup2(execs[i]->pipe[0], STDIN_FILENO);
		close(execs[i]->pipe[0]);
		close(execs[i]->pipe[1]);
	}
	if (execs[i]->has_redir_out == true)
	{
		dup2(execs[i]->pipe[1], STDOUT_FILENO);
	}

}

int	execute(t_exec	**execs)
{
	ssize_t	i;

	i = -1;
	while (execs[++i])
	{
		set_pipes(execs, i);
		execs[i]->pid = fork();
		if (!execs[i]->pid)
			child_exec(execs, i);
	}

}

int	execution(t_cmd **cmds)
{
	t_exec	**execs;

	execs = init_execs(cmds);
	if (has_scopes(execs))
	{
	}

}


//paranthesis
//pipes
//redirs
//statuses
