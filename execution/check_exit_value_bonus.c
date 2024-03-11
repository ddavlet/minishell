#include "execution.h"

static int	is_part_of_logic_operation(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	if (previous_cmd_connected_through_operation(exec)
		&& (previous_cmd_in_execution(exec)->operat == AND
			|| previous_cmd_in_execution(exec)->operat == OR))
		return (1);
	else if (next_cmd_connected_through_operation(exec)
		&& (current_cmd_in_execution(exec)->operat == AND
			|| current_cmd_in_execution(exec)->operat == OR))
		return (1);
	return (0);
}

void	debug_check_exit_value(t_executor *exec, t_scope *scope)
{
	ft_putendl_fd("::::::::::::::::::::::::", 2);
	ft_putendl_fd("DEBUG::check_exit_value", 2);
	ft_putstr_fd("DEBUG::pid: ", 2);
	ft_putnbr_fd(scope->pid, 2);
	ft_putstr_fd("::status: ", 2);
	ft_putnbr_fd(exec->status, 2);
	ft_putstr_fd("::scope_id: ", 2);
	ft_putnbr_fd(scope->scope_id, 2);
	ft_putstr_fd("::command_index: ", 2);
	ft_putnbr_fd(exec->command_index, 2);
	ft_putendl_fd("", 2);
	ft_putstr_fd("DEBUG::out_fd::", 2);
	ft_putendl_fd(ft_itoa(exec->output_fd->fd), 2);
	ft_putstr_fd("DEBUG::in_fd::", 2);
	ft_putendl_fd(ft_itoa(exec->input_fd->fd), 2);
	if (scope->pipe)
	{
		ft_putstr_fd("DEBUG::pipe->read::", 2);
		ft_putendl_fd(ft_itoa(scope->pipe->read->fd), 2);
		ft_putstr_fd("DEBUG::pipe->write::", 2);
		ft_putendl_fd(ft_itoa(scope->pipe->write->fd), 2);
	}
	else
		ft_putendl_fd("DEBUG::pipe::NULL", 2);

}

int	check_exit_value(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	if (scope->pipe && current_cmd_in_execution(exec) != NULL)
	{
		close_fd(scope->pipe->write, exec);
		debug_check_exit_value(exec, scope);
	ft_putendl_fd("::fd_state before waitpid::", 2);
	ft_putstr_fd("DEBUG::out_fd->is_open::", 2);
	ft_putendl_fd(ft_itoa(exec->output_fd->is_open), 2);
	ft_putstr_fd("DEBUG::in_fd->is_open::", 2);
	ft_putendl_fd(ft_itoa(exec->input_fd->is_open), 2);
	if (scope->pipe)
	{
		ft_putstr_fd("DEBUG::pipe->read->is_open::", 2);
		ft_putendl_fd(ft_itoa(scope->pipe->read->is_open), 2);
		ft_putstr_fd("DEBUG::pipe->write->is_open::", 2);
		ft_putendl_fd(ft_itoa(scope->pipe->write->is_open), 2);
	}
	else
		ft_putendl_fd("DEBUG::pipe::NULL", 2);

		// ft_putstr_fd("DEBUG::cmd[", 2);
		// ft_putnbr_fd(exec->command_index, 2);
		// ft_putendl_fd("]", 2);
		// ft_putstr_fd("DEBUG::close_fd::pipe->write: ", 2);
		// ft_putendl_fd(ft_itoa(scope->pipe->write->fd), 2);
	}
	else
		debug_check_exit_value(exec, scope);
	if (is_part_of_logic_operation(exec, scope))
	{
		waitpid(scope->pid, &(exec->status), 0);
		evaluate_and_or(exec);
	}
	else if (current_cmd_in_execution(exec) == final_cmd_in_scope(exec, scope))
		waitpid(scope->pid, &(exec->status), 0);
	return (0);
}
