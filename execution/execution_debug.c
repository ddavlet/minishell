#include "execution.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


t_cmd   **mockup_three_cmds(void)
{
    t_cmd   **cmds;
    t_cmd   *cmd1;
    t_cmd   *cmd2;
    t_cmd   *cmd3;

// First
    cmd1 = (t_cmd *)malloc(sizeof(t_cmd));
    cmd1->com = ft_strdup("ls");
    cmd1->legit = true;
    cmd1->operat = PIPE;
    cmd1->argv = (char **)malloc(sizeof(char *) * 3);
    cmd1->argv[0] = ft_strdup("ls");
    cmd1->argv[1] = ft_strdup("-l");
    cmd1->argv[2] = NULL;

    t_redir *redir1 = malloc(sizeof(t_redir));
    redir1->redir_sym = NO_REDIR;
    redir1->redir_name = NULL;
    cmd1->redirs = redir1;

// Second
    cmd2 = (t_cmd *)malloc(sizeof(t_cmd));
    cmd2->legit = true;
    cmd2->operat = PIPE;
    cmd2->com = ft_strdup("grep");
    cmd2->argv = (char **)malloc(sizeof(char *) * 3);
    cmd2->argv[0] = ft_strdup("grep");
    cmd2->argv[1] = ft_strdup("exe*");
    cmd2->argv[2] = NULL;

    t_redir *redir2 = malloc(sizeof(t_redir));
    redir2->redir_sym = NO_REDIR;
    redir2->redir_name = NULL;
    cmd2->redirs = redir2;

// Third
    cmd3 = (t_cmd *)malloc(sizeof(t_cmd));
    cmd3->legit = true;
    cmd3->operat = PIPE;
    cmd3->com = ft_strdup("wc");
    cmd3->argv = (char **)malloc(sizeof(char *) * 3);
    cmd3->argv[0] = ft_strdup("wc");
    cmd3->argv[1] = ft_strdup("-l");
    cmd3->argv[2] = NULL;

    t_redir *redir3 = malloc(sizeof(t_redir));
    redir3->redir_sym = NO_REDIR;
    redir3->redir_name = NULL;
    cmd3->redirs = redir3;

// Assign to array
    cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 4);
    cmds[0] = cmd1;
    cmds[1] = cmd2;
    cmds[2] = cmd3;
    cmds[3] = NULL;
    return (cmds);
}

t_cmd **mockup_single_cmd(void)
{
    t_cmd   **cmds;
    t_cmd   *cmd;

    cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 2);
    
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    cmd->com = ft_strdup("ls");
    cmd->legit = true;
    cmd->operat = RUN;
    cmd->argv = (char **)malloc(sizeof(char *) * 2);
    cmd->argv[0] = ft_strdup("ls");
    cmd->argv[1] = NULL;

    t_redir *redir = malloc(sizeof(t_redir));
    redir->redir_sym = HEAR_DOC;
    redir->redir_name = ft_strdup("EOF");
    cmd->redirs = redir;

    cmds[0] = cmd;
    cmds[1] = NULL;

    return (cmds);
}

t_cmd   **mockup_empty_cmds(void)
{
    t_cmd   **cmds;

    cmds = (t_cmd **)malloc(sizeof(t_cmd *));
    cmds[0] = NULL;
    return (cmds);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	**cmds;

	(void)argc;
	(void)argv;
	// cmds = mockup_three_cmds();
    cmds = mockup_single_cmd();
	if (cmds == NULL)
		terminate_execution(cmds, envp);
	execute_command_line(cmds, envp);
	terminate_execution(cmds, envp);
	return (0);
}