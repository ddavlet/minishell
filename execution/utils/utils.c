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

unsigned long	rand_simple(void)
{
	static unsigned long	lcg_prev = 21512345435143;
	const unsigned long		a = 1103515245;
	const unsigned long		c = 12345;

	const unsigned long m = 1UL << 31; // 2^31
	lcg_prev = (a * lcg_prev + c) % m;
	return (lcg_prev);
}

void	exit_handler(int status)
{
	if (status == 0)
		exit(0);
	else
		exit(status);
}

void	terminate(t_executor *exec, t_scope *scope, int status)
{
	if (exec)
		free(exec);
	if (scope)
	{
		close(scope->pipe->read->fd);
		free(scope->pipe->read);
		close(scope->pipe->write->fd);
		free(scope->pipe->write);
		free(scope->pipe);
		free(scope);
	}
	exit_handler(status);
}

int	is_last(t_executor *exec)
{
	if (exec->cmds[exec->command_index + 1] == NULL)
		return (1);
	return (0);
}

int	execution_has_finished(t_executor *exec)
{
	t_cmd	*cmd;

	cmd = exec->cmds[exec->command_index];
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

	cmd = exec->cmds[exec->command_index]->com;
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

int	is_inside_scope(t_executor *exec, t_scope *scope)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = current_cmd_in_execution(exec);
    if (cmd)
    {
        while (cmd->scope_stack[i] && cmd->scope_stack[i] != scope->scope_id)
            i++;
        if (cmd->scope_stack[i] == scope->scope_id)
            return (1);
    }
	return (0);
}

int	has_nested_scope(t_executor *exec, t_scope *scope)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = current_cmd_in_execution(exec);
	while (cmd->scope_stack[i])
		i++;
	if (cmd->scope_stack[i - 1] != scope->scope_id)
		return (1);
	return (0);
}

int	param_check(t_executor *exec, t_scope *scope)
{
	if (!exec || !exec->cmds || !exec->cmds[exec->command_index] || !scope)
		return (-1);
	return (0);
}

int	find_nested_id(t_executor *exec, t_scope *scope)
{
	t_cmd	*cmd;
	int		i;

	cmd = current_cmd_in_execution(exec);
	i = 0;
	while (cmd->scope_stack[i] != scope->scope_id)
		i++;
	if (cmd->scope_stack[i] && cmd->scope_stack[i + 1])
		return (cmd->scope_stack[i + 1]);
	return (0);
}

int	connected_through_operation(t_cmd *comparison, t_cmd *other)
{
	int	last_common_scope;
	int	actual_scope;

	if (!comparison || !other)
		return (0);
	last_common_scope = 0;
	while (comparison->scope_stack[last_common_scope] == other->scope_stack[last_common_scope])
		last_common_scope++;
	while (comparison->scope_stack[actual_scope])
		actual_scope++;
	if (last_common_scope - actual_scope > 1)
		return (0);
	return (1);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_cmd	*current_cmd_in_execution(t_executor *exec)
{
	if (!exec)
	{
		ft_putendl_fd("executor missing", 2);
		terminate(NULL, NULL, EXIT_FAILURE);
	}
	return (exec->cmds[exec->command_index]);
}

t_cmd	*previous_cmd_in_execution(t_executor *exec)
{
	if (!exec)
	{
		ft_putendl_fd("executor missing", 2);
		terminate(NULL, NULL, EXIT_FAILURE);
	}
	if (exec->command_index == 0)
		return (NULL);
	return (exec->cmds[exec->command_index - 1]);
}

t_cmd	*next_cmd_in_execution(t_executor *exec)
{
	if (!exec)
	{
		ft_putendl_fd("executor missing", 2);
		terminate(NULL, NULL, EXIT_FAILURE);
	}
	if (exec->cmds[exec->command_index] == NULL)
		return (NULL);
	return (exec->cmds[exec->command_index + 1]);
}

int get_scope(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->scope_stack[i])
        i++;
    return (i - 1);
}

int get_outside_scope(t_cmd *cmd)
{
    return (get_scope(cmd) - 1);
}

t_cmd	*last_cmd_in_scope(t_executor *exec, t_scope *scope)
{
	int i;
	t_cmd *cmd;

	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE);
	cmd = current_cmd_in_execution(exec);
	i = 1;
	while (get_scope(cmd) == scope->scope_id)
		cmd = exec->cmds[exec->command_index + (i++)];
	return (cmd);
}

t_cmd   *next_command(t_executor *exec, t_cmd *cmd)
{
    int i;

    i = 0;
    while (exec->cmds[i] && exec->cmds[i] != cmd)
        i++;
    return (exec->cmds[i]);
}

t_cmd   *last_cmd_in_execution(t_executor *exec)
{
    int i;

    i = exec->command_index;
    while (exec->cmds[i])
        i++;
    return (exec->cmds[i - 1]);
}