#include "../execution.h"

void	free_arr2d(void **arr2d)
{
	int		i;
	char	**arr;

	arr = (char **)arr2d;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	msg_error(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

void	exit_handler(int status)
{
	if (status == 0)
		exit(0);
	else
		exit(status);
}

void	terminate(t_executor *exec, int status, char *msg)
{
	if (exec)
	{
		terminate_commands(exec->cmds);
		free(exec);
	}
	if (msg)
		msg_error(msg);
	exit(status);
}

int	is_final(t_executor *exec)
{
	t_cmd	*cmd;

	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE, "is_final: missing or incomplete exec");
	cmd = get_current_cmd(exec);
	if (has_nested_scope(cmd))
		cmd = final_cmd_in_scope(exec, cmd->scope_stack[1]);
	if (get_next_cmd(exec, cmd) == NULL)
		return (1);
	return (0);
}

int	execution_has_finished(t_executor *exec)
{
	t_cmd	*cmd;

	cmd = get_current_cmd(exec);
	if (cmd == NULL)
		return (1);
	return (0);
}

int	is_inside_scope(t_cmd *cmd, int scope)
{
	int	i;

	if (scope < 1)
		terminate(NULL, EXIT_FAILURE, "is_inside_scope: invalid scope");
	i = 0;
	if (cmd)
	{
		while (cmd->scope_stack[i] && cmd->scope_stack[i] != scope)
			i++;
		if (cmd->scope_stack[i] == scope)
			return (1);
	}
	return (0);
}

int	has_nested_scope(t_cmd *cmd)
{
	int	i;

	i = 0;
    if (cmd)
    {
        while (cmd->scope_stack[i])
            i++;
        if (cmd->scope_stack[i - 1] > SCOPE)
            return (1);
    }
	return (0);
}

int	scope_length(t_executor *exec, t_cmd *cmd, int scope)
{
	int		len;

	if (!exec || !cmd || scope == 0)
		terminate(NULL, EXIT_FAILURE, "scope_length: parameter check failed");
	len = 0;
	while (is_inside_scope(cmd, scope))
	{
		len++;
		cmd = get_next_cmd(exec, cmd);
	}
	if (!len)
	{
		terminate(NULL, EXIT_FAILURE, "scope_length: command not inside scope");
	}
	return (len);
}

int	get_nested_scope(t_cmd *cmd)
{
	if (!cmd->scope_stack[1])
		terminate(NULL, EXIT_FAILURE, "get_nested_scope: no nested scope");
	return (cmd->scope_stack[1]);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}


int	get_scope(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (-1);
	i = 0;
	while (cmd->scope_stack[i])
		i++;
	return (cmd->scope_stack[i - 1]);
}

t_cmd	*final_cmd_in_scope(t_executor *exec, int scope)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (!exec)
		terminate(NULL, EXIT_FAILURE, "parameter check failed");
	cmd = get_current_cmd(exec);
	next = get_next_cmd(exec, cmd);
	while (is_inside_scope(next, scope))
	{
		cmd = next;
		next = get_next_cmd(exec, cmd);
	}
	return (cmd);
}

t_cmd	*first_cmd_in_scope(t_executor *exec, int scope)
{
	t_cmd	*cmd;
	t_cmd	*prev;

	if (!exec)
		terminate(NULL, EXIT_FAILURE, "parameter check failed");
	cmd = get_previous_cmd(exec, get_current_cmd(exec));
	prev = get_previous_cmd(exec, cmd);
	while (is_inside_scope(prev, scope))
	{
		cmd = prev;
		prev = get_previous_cmd(exec, cmd);
	}
	return (cmd);
}


void	close_fd(t_fd_state *fd_state)
{
	if (!fd_state)
		terminate(NULL, EXIT_FAILURE,
			"close_fd: couldn't close file descriptor");
	// debug_close_fd(fd_state);
	if (fd_state->is_open == 0)
		terminate(NULL, EXIT_FAILURE,
			"close_fd: file descriptor already closed");
    else if (close(fd_state->fd) == -1)
		terminate(NULL, EXIT_FAILURE, "Couldn't close file descriptor");
	fd_state->is_open = 0;
}

int	count_pipes(t_executor *exec, bool include_nested_scopes)
{
	t_cmd	*cmd;
	int		count;

	count = 0;
	cmd = exec->cmds[0];
	while (cmd)
	{
		if (include_nested_scopes && has_nested_scope(cmd))
			cmd = final_cmd_in_scope(exec, cmd->scope_stack[1]);
		if (cmd->operat == PIPE)
			count++;
		cmd = get_next_cmd(exec, cmd);
	}
	return (count);
}

void	skip_nested_cmds(t_executor *exec)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*next;

	i = 1;
	cmd = get_current_cmd(exec);
	next = get_next_cmd(exec, cmd);
	while (is_inside_scope(next, get_nested_scope(cmd)))
	{
		cmd = next;
		next = get_next_cmd(exec, cmd);
		i++;
	}
	exec->command_index += i;
}

t_pipe	*next_pipe(t_pipe **pipes)
{

	int	i;

	i = 0;
	while (pipes[i]->write->is_open == 0)
		i++;
    return (pipes[i]);
}

t_pipe	*last_pipe(t_pipe **pipes)
{
	int	i;

	i = 0;
	while (pipes[i] && pipes[i]->write->is_open == 0)
		i++;
    return (pipes[i - 1]);
}

int get_execution_length(t_executor *exec)
{
    int     len;
    t_cmd   **cmds;

    if (!exec || exec->cmds)
        terminate(exec, EXIT_FAILURE, "couldn't get execution length");
    cmds = exec->cmds;
    len = 0;
    while (cmds[len])
        len++;
    return (len);
}


int	is_builtin(t_executor *exec)
{
    char    *name;

    name = get_current_cmd(exec)->argv[0];
	if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0 || ft_strncmp(name, "echo",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "env", ft_strlen(name) + 1) == 0
		|| ft_strncmp(name, "exit", ft_strlen(name) + 1) == 0 || ft_strncmp(name,
			"export", ft_strlen(name) + 1) == 0 || ft_strncmp(name, "pwd",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "unset",
			ft_strlen(name) + 1) == 0)
		return (1);
	return (0);
}
