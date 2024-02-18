
#include "execution.h"

int	execution(t_pars **cmd_arr, char *envp[])
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = 0;
	while (cmd_arr[i])
	{
		if (cmd_arr[i]->operat == AND)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(cmd_arr[i]->name, cmd_arr[i]->args, envp) == -1)
				{
					perror("execve");
					exit(1);
				}
			}
			else if (pid > 0)
			{
				waitpid(pid, NULL, 0);
			}
			else
			{
				perror("fork");
				exit(1);
			}
		}
		else if (cmd_arr[i]->operat == OR)
		{
				pid = fork();
				if (pid == 0)
				{
					if (execve(cmd_arr[i]->name, cmd_arr[i]->args, envp) == -1)
					{
						perror("execve");
						exit(1);
					}
				}
				else if (pid > 0)
				{
					waitpid(pid, NULL, 0);
				}
				else
				{
					perror("fork");
					exit(1);
				}
		}
		else
		if (cmd_arr[i]->operat == PIPE)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(1);
			}
			pid = fork();
			if (pid == 0)
			{
				// CHILD
				dup2(fd[1], 1); // redirect stdout to the write end of the pipe
				close(fd[0]);
				close(fd[1]);
				if (execve(cmd_arr[i]->name, cmd_arr[i]->args, envp) == -1)
				{
					perror("execve");
					exit(1);
				}
			}
			else if (pid > 0) 
			{
				// PARENT
				dup2(fd[0], 0); // redirect stdin to the read end of the pipe
				close(fd[0]);
				close(fd[1]);
				waitpid(pid, NULL, 0);
			}
			else
			{
				perror("fork");
				exit(1);
			}
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(cmd_arr[i]->name, cmd_arr[i]->args, envp) == -1)
				{
					perror("execve");
					exit(1);
				}
			}
			else if (pid > 0)
			{
				waitpid(pid, NULL, 0);
			}
			else
			{
				perror("fork");
				exit(1);
			}
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	// t_pars	**commands = parse_text(argv[1]);
	t_pars	**commands = parse_text("ls -l | grep .c | wc -l");

	debug_print_parse(commands);
	execution(commands, envp);

	(void)argc;
	(void)argv;
	return (0);
}
