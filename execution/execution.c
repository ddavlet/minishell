
#include "execution.h"

int	execute_command(t_com *cmd, char *envp[])
{
	char	**argv;
	char	*cmd_name;
	char	*path;

	cmd_name = cmd->com;
	create_argv(cmd, &argv);
	if (argv == NULL)
	{
		terminate_command(cmd);
		return (-1);
	}
	path = get_path(cmd_name, envp);
	if (path == NULL)
	{
		free(path);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_name, 2);
		terminate_command(cmd);
		return (-1);
	}
	if (execve(path, argv, envp) == -1)
	{
		free(path);
		ft_putstr_fd("pipex: execve", 2);
		ft_putendl_fd(cmd_name, 2);
		free_string_arr(argv);
		return (-1);
	}
}

int	execute_chain_of_commands(t_com **cmds, char *envp[])
{
	int		fd[2]; // f[0] - read, f[1] - write
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	while (cmds[i + 1])
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			terminate_execution();
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			terminate_execution();
		}
		if (pid == 0) 
		{
			close(fd[0]); 
			dup2(fd[1], 1);
			close(fd[1]);
			execute_command(cmds[i], envp);
		}
		else
		{
			waitpid(pid, &status, 0);
			close(fd[1]);
			dup2(fd[0], 0); // redirect stdin to read end of pipe
			close(fd[0]);
			execute_command(cmds[i + 1], envp);

			i++;
		}
	}

}

int	execution(t_com **cmds, char *envp[])
{
	if (!cmds || cmds[0] == NULL)
		terminate_execution(cmds, envp);
	else if (cmds[1] == NULL)
		execute_command(cmds[0], envp);
	else
		execute_chain_of_commands(cmds, envp);
	return (0);
}
