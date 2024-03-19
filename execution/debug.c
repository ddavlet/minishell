#include "../libft/libft.h"
#include "execution.h"
#include <stdlib.h>
#include <string.h> // For memcpy
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char *argv[],const char *envp[])
{
	t_cmd **cmds;

	(void)argc;
	(void)argv;
	t_env *env = init_env((const char **)envp);

	cmds = parse_text("cat | cat | ls ", env);
		// wildcard parsing error: No such file or directory
	execution(cmds, (char **)envp);
	return (0);
}

void    debug_close_fd(t_fd_state *fd_state)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putstr_fd("DEBUG::closing fd: ", 2);
    ft_putnbr_fd(fd_state->fd, 2);
    ft_putendl_fd("", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_pipe_information(t_pipe *pipe)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd(":pipe information:", 2);
    ft_putstr_fd("DEBUG::write fd: ", 2);
    ft_putnbr_fd(pipe->write->fd, 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::read fd: ", 2);
    ft_putnbr_fd(pipe->read->fd, 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::write is_open: ", 2);
    ft_putnbr_fd(pipe->write->is_open, 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::read is_open: ", 2);
    ft_putnbr_fd(pipe->read->is_open, 2);
    ft_putendl_fd("", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_started(char *msg)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putstr_fd(msg, 2);
    ft_putendl_fd(" started", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_ended(char *msg)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putstr_fd(msg, 2);
    ft_putendl_fd(" ended", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_cmd_info(t_executor *exec)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd(":cmd information:", 2);
    ft_putstr_fd("DEBUG::cmd: ", 2);
    ft_putstr_fd(exec->cmds[exec->command_index]->argv[0], 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::index: ", 2);
    ft_putnbr_fd(exec->command_index, 2);
    ft_putendl_fd("", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

