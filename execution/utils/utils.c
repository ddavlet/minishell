#include "../execution.h"

void	free_arr2d(void **arr2d)
{
	int	i;
    char **arr;

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
	const unsigned long		m = 1UL << 31; // 2^31

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
    t_cmd   *cmd;

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
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "echo", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "env", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "exit", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "export", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "pwd", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "unset", ft_strlen(cmd) == 0)
		)
		return (1);
	return (0);
}

int	has_nested_scope(t_executor *exec, t_scope *scope)
{
	t_cmd	*cmd;
    int     i;

    cmd = exec->cmds[exec->command_index];
    i = 0;
    while (cmd->scope_stack[i + 1] != NULL)
        i++;
    if (cmd->scope_stack[i] != scope->scope_id)
        return (1);
	return (0);
}

int param_check(t_executor *exec, t_scope *scope)
{
    if (!exec || !exec->cmds || !exec->cmds[exec->command_index] || !scope)
        return (-1);
    return (0);
}

int	check_exit_value(t_executor *exec, t_scope *scope)
{
	waitpid(scope->pid, &(exec->status), 0);
	print_exit_info(exec->status);
	if (exec->status != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putendl_fd(strerror(exec->status), 2);
	}
}

int find_nested_id(t_executor *exec, t_scope *scope)
{
    t_cmd   *cmd;
    int     i;

    cmd = current_cmd_in_execution(exec);
    i = 0;
    while (cmd->scope_stack[i] != scope->scope_id)
        i++;
    if (cmd->scope_stack[i] && cmd->scope_stack[i + 1])
        return (cmd->scope_stack[i + 1]);
    return (0);
}
