
#include "execution.h"

int	execute_command(t_cmd *cmd, char *envp[])
{
	char	*cmd_name;
	char	*path;

	cmd_name = cmd->com;
	if (cmd->argv == NULL)
	{
		terminate_execution((t_cmd **)NULL, envp);
		return (-1);
	}
	path = get_path(cmd_name, envp);
	if (path == NULL)
	{
		free(path);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_name, 2);
		terminate_execution((t_cmd **)NULL, envp);
		return (-1);
	}
	if (execve(path, cmd->argv, envp) == -1)
	{
		free(path);
		ft_putstr_fd("pipex: execve", 2);
		ft_putendl_fd(cmd_name, 2);
		free_string_arr(cmd->argv);
		return (-1);
	}
	return (0);
}

int	execute_chain_of_commands(t_cmd **cmds, char *envp[])
{
	int		fd[2];
	int		in_fd = 0; // in_fd will be used to keep track of the input for the next command
	pid_t	pid;
	int		status;
	int		i = 0;

	while (cmds[i] != NULL)
	{
		if (cmds[i + 1] != NULL) // If there's a next command, set up a pipe
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				terminate_execution(cmds, envp);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			terminate_execution(cmds, envp);
		}
		if (pid == 0) // Child process
		{
			in_fd = determine_input_fd(cmds[i], in_fd);
			if (cmds[i + 1] != NULL) // Not the last command
			{
				dup2(fd[1], STDOUT_FILENO); // dup2 will close STDOUT_FILENO before duplicating fd[1] to STDOUT_FILENO
				close(fd[1]); 
				close(fd[0]); 
			}
			if (in_fd != 0) // If this is not the first command
			{
				dup2(in_fd, STDIN_FILENO); // Redirect stdin from previous pipe
				close(in_fd); // No need for the old in_fd after dup2
			}
			execute_command(cmds[i], envp);
			exit(0);
		}
		else // Parent process
		{
			waitpid(pid, &status, 0); // Wait for the child process to finish
			if (in_fd != 0)
				close(in_fd); // Close the old in_fd
			in_fd = fd[0]; // Save the read end of the pipe for the next command
			close(fd[1]); // Close the write end of the pipe in the parent
			if (cmds[i + 1] == NULL) // If this was the last command
				close(in_fd); // Close the last read end
		}
		i++;
	}
	return 0; // Return success
}

int	execute_command_line(t_cmd **cmds, char *envp[])
{
	if (!cmds || cmds[0] == NULL)
		terminate_execution(cmds, envp);
	else if (cmds[1] == NULL)
		execute_command(cmds[0], envp);
	else
		execute_chain_of_commands(cmds, envp);
	return (0);
}
