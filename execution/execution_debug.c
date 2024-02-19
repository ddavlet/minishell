#include "execution.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


t_com   **mockup_three_cmds(void)
{
    t_com   **cmds;
    t_com   *cmd1;
    t_com   *cmd2;
    t_com   *cmd3;

    cmds = (t_com **)malloc(sizeof(t_com *) * 4);

    cmd1 = (t_com *)malloc(sizeof(t_com));
    cmd1->com = ft_strdup("ls");
    cmd1->legit = true;
    cmd1->operat = PIPE;
    cmd1->redir_sym = NO_REDIR;
    cmd1->redir_name = NULL;
    cmd1->args = (char **)malloc(sizeof(char *) * 3);
    cmd1->args[0] = ft_strdup("ls");
    cmd1->args[1] = ft_strdup("-l");
    cmd1->args[2] = NULL;

    cmd2 = (t_com *)malloc(sizeof(t_com));
    cmd2->legit = true;
    cmd2->operat = PIPE;
    cmd2->redir_sym = NO_REDIR;
    cmd2->redir_name = NULL;
    cmd2->com = ft_strdup("grep");
    cmd2->args = (char **)malloc(sizeof(char *) * 3);
    cmd2->args[0] = ft_strdup("grep");
    cmd2->args[1] = ft_strdup("exe*");
    cmd2->args[2] = NULL;

    cmd3 = (t_com *)malloc(sizeof(t_com));
    cmd3->legit = true;
    cmd3->operat = PIPE;
    cmd3->redir_sym = NO_REDIR;
    cmd3->redir_name = NULL;
    cmd3->com = ft_strdup("wc");
    cmd3->args = (char **)malloc(sizeof(char *) * 3);
    cmd3->args[0] = ft_strdup("wc");
    cmd3->args[1] = ft_strdup("-l");
    cmd3->args[2] = NULL;

    cmds[0] = cmd1;
    cmds[1] = cmd2;
    cmds[2] = cmd3;
    cmds[3] = NULL;
    return (cmds);
}

t_com **mockup_single_cmd(void)
{
    t_com   **cmds;
    t_com   *cmd;

    cmds = (t_com **)malloc(sizeof(t_com *) * 2);
    
    cmd = (t_com *)malloc(sizeof(t_com));
    cmd->com = ft_strdup("ls");
    cmd->legit = true;
    cmd->operat = RUN;
    cmd->redir_sym = NO_REDIR;
    cmd->redir_name = NULL;
    cmd->args = (char **)malloc(sizeof(char *) * 2);
    cmd->args[0] = ft_strdup("ls");
    cmd->args[1] = NULL;

    cmds[0] = cmd;
    cmds[1] = NULL;

    return (cmds);
}

t_com   **mockup_empty_cmds(void)
{
    t_com   **cmds;

    cmds = (t_com **)malloc(sizeof(t_com *));
    cmds[0] = NULL;
    return (cmds);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_com	**cmds;

	(void)argc;
	(void)argv;
	cmds = mockup_three_cmds();
	if (cmds == NULL)
		terminate_execution(cmds, envp);
	execute_command_line(cmds, envp);
	terminate_execution(cmds, envp);
	return (0);
}