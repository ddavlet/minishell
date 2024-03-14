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
		free(exec);
	if (msg)
		msg_error(msg);
	exit_handler(status);
}

int	is_final(t_executor *exec)
{
	t_cmd	*cmd;

	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"is_final: missing or incomplete exec");
    cmd = current_cmd(exec);
	if (is_nested_scope(cmd))
		cmd = final_cmd_in_scope(exec, cmd->scope_stack[1]);
	if (next_cmd(exec, cmd) == NULL)
		return (1);
	return (0);
}


int	execution_has_finished(t_executor *exec)
{
	t_cmd	*cmd;

	cmd = current_cmd(exec);
	if (cmd == NULL)
		return (1);
	return (0);
}

char	*get_name(char *cmd_path)
{
	char	*last;

	last = NULL;
	while (cmd_path)
	{
		last = cmd_path;
		cmd_path = ft_strchr(cmd_path, '/');
	}
	return (last);
}

int	is_builtin(t_executor *exec)
{
	char	*cmd;

	cmd = current_cmd(exec)->com;
	if (ft_strchr(cmd, '/'))
	{
		cmd = get_name(cmd);
		if (!cmd)
			return (0);
	}
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd) == 0) || ft_strncmp(cmd, "echo",
			ft_strlen(cmd) == 0) || ft_strncmp(cmd, "env", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "exit", ft_strlen(cmd) == 0) || ft_strncmp(cmd,
			"export", ft_strlen(cmd) == 0) || ft_strncmp(cmd, "pwd",
			ft_strlen(cmd) == 0) || ft_strncmp(cmd, "unset",
			ft_strlen(cmd) == 0))
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

int	is_nested_scope(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->scope_stack[i])
		i++;
	if (cmd->scope_stack[i - 1] > SCOPE)
		return (1);
	return (0);
}

int	scope_length(t_executor *exec, int scope)
{
	t_cmd	*cmd;
	int		len;

	if (!exec || !exec->cmds || scope == 0)
		terminate(NULL, EXIT_FAILURE,
			"scope_length: parameter check failed");
	len = 1;
	cmd = next_cmd_in_execution(exec);
	while (is_inside_scope(cmd, scope))
	{
		len++;
		cmd = next_cmd(exec, cmd);
	}
	return (len);
}

int	get_nested_scope(t_executor *exec)
{
	t_cmd	*cmd;

	cmd = current_cmd(exec);
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

t_cmd	*current_cmd(t_executor *exec)
{
	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"current_cmd: missing or incomplete exec");
	return (exec->cmds[exec->command_index]);
}

t_cmd	*previous_cmd_in_execution(t_executor *exec)
{
	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"previous_cmd_in_execution: missing or incomplete exec");
	if (exec->command_index == 0)
		return (NULL);
	return (exec->cmds[exec->command_index - 1]);
}

t_cmd	*next_cmd_in_execution(t_executor *exec)
{
	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"next_cmd_in_execution: missing or incomplete exec");
	if (current_cmd(exec) == NULL)
		return (NULL);
	return (exec->cmds[exec->command_index + 1]);
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

int	get_outside_scope(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->scope_stack[i])
		i++;
	return (cmd->scope_stack[i - 2]);
}

t_cmd	*final_cmd_in_scope(t_executor *exec, int scope)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (!exec)
		terminate(NULL, EXIT_FAILURE, "parameter check failed");
	cmd = current_cmd(exec);
	next = next_cmd(exec, cmd);
	while (is_inside_scope(next, scope))
	{
		cmd = next;
		next = next_cmd(exec, cmd);
	}
	return (cmd);
}

t_cmd	*next_cmd(t_executor *exec, t_cmd *cmd)
{
	int	i;

	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE,
			"next_cmd: missing or incomplete exec");
	i = 0;
	if (cmd == NULL)
		return (NULL);
	while (exec->cmds[i] != cmd && exec->cmds[i + 1] != NULL)
		i++;
	return (exec->cmds[i + 1]);
}

t_cmd    *previous_cmd(t_executor *exec, t_cmd *cmd)
{
    int	i;

    if (!exec || !exec->cmds)
        terminate(NULL, EXIT_FAILURE,
            "previous_cmd: missing or incomplete exec");
    i = 0;
    if (cmd == NULL)
        return (NULL);
    if (exec->command_index == 0)
        return (NULL);
    while (exec->cmds[i] != cmd && exec->cmds[i + 1] != NULL)
        i++;
    return (exec->cmds[i - 1]);
}

void	close_fd(t_fd_state *fd_state)
{
	if (!fd_state)
		terminate(NULL, EXIT_FAILURE,
			"close_fd: couldn't close file descriptor");
	if (fd_state->is_open == 0)
		terminate(NULL, EXIT_FAILURE,
			"close_fd: file descriptor already closed");
	else if (close(fd_state->fd) == -1)
		terminate(NULL, EXIT_FAILURE, "Couldn't close file descriptor");
	fd_state->is_open = 0;
}

char	**argv(t_executor *exec)
{
	t_cmd	*cmd;

	if (!exec || !exec->cmds)
		return (NULL);
	cmd = current_cmd(exec);
	return (cmd->argv);
}

char	**envp(t_executor *exec)
{
	t_cmd *cmd;

	if (!exec || !exec->cmds)
		return (NULL);
	cmd = current_cmd(exec);
	return (cmd->env->envp);
}

