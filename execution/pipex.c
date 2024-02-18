#include "pipex.h"

void	execute_command(char *cmd, char *envp[])
{
	char	*path;
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	remove_inner_quotes(cmd_split);
	path = get_path(cmd_split[0], envp);
	if (path == NULL)
	{
		free(path);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_split[0], 2);
		free_string_arr(cmd_split);
		exit(-1);
	}
	if (execve(path, cmd_split, envp) == -1)
	{
		free(path);
		ft_putstr_fd("pipex: execve", 2);
		ft_putendl_fd(cmd_split[0], 2);
		free_string_arr(cmd_split);
		exit(-1);
	}
}

void	parent_process(int pipe_fd[2], char *argv[], char *envp[])
{
	int	fd;

	if (access(argv[4], F_OK) == -1)
		perror("pipex");
	else if (access(argv[4], R_OK) == -1)
		perror("pipex");
	else
	{
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(-1);
		dup2(fd, STDOUT_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		execute_command(argv[3], envp);
	}
}

void	child_process(int pipe_fd[2], char *argv[], char *envp[])
{
	int	fd;

	if (access(argv[1], F_OK) == -1)
		perror("pipex");
	else if (access(argv[1], R_OK) == -1)
		perror("pipex");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(-1);
		dup2(fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		execute_command(argv[2], envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (argc < 5)
	{
		ft_putstr_fd("USAGE: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 2);
		exit(-1);
	}
	if (argc == 5)
	{
		if (pipe(pipe_fd) == -1)
			exit(-1);
		pid = fork();
		if (pid == -1)
			exit(-1);
		if (pid == 0)
			child_process(pipe_fd, argv, envp);
		else
		{
			parent_process(pipe_fd, argv, envp);
			waitpid(pid, &status, 0);
		}
	}
	else if (argc > 5)
	{
		int	cmd_count = count_cmd(argc, argv, envp);

		while (cmd_count > 0)
		{
			if (pipe(pipe_fd) == -1)
				terminate_pipex();
			pid = fork();
			if (pid == -1)
				terminate_pipex();
			if (pid == 0)
			{}
			else
			{}
		}
	}
	return (0);
}

int	count_cmd(int argc, char *argv[], char *envp[])
{
	char	*path;
	char	**cmd_split;
	int		i;

	i = 1;
	while (i < argc - 1)
	{
		cmd_split = ft_split(argv[i], ' ');
		path = get_path(cmd_split[0], envp);
		if (path == NULL)
		{
			free_string_arr(cmd_split);
			ft_putstr_fd("pipex: ", 2);
			ft_putendl_fd(cmd_split[0], 2);
			exit(-1);
		}
		if (access(path, F_OK || X_OK) == -1)
		{
			free(path);
			free_string_arr(cmd_split);
			ft_putendl_fd("USAGE: ./pipex <infile> <cmd1> <cmd2> <outfile>", 2);
			exit(-1);
		}
		i++;
	}
	return (i - 1);
}
