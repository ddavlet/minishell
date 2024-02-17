
#include "execution.h"

int	execution(t_pars **cmd_arr)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = 0;
	while (cmd_arr[i])
	{
		if (cmd_arr[i]->operat == PIPE)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				// CHILD
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				if (execve(cmd_arr[i]->name, cmd_arr[i]->args, NULL) == -1)
				{
					perror("execve");
					exit(1);
				}
			}
			else if (pid > 0)
			{
				// PARENT
				dup2(fd[0], 0);
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
				if (execve(cmd_arr[i]->name, cmd_arr[i]->args, NULL) == -1)
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