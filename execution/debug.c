#include "execution.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void free_mockup_cmds(t_cmd **cmds)
{
    int i;
    int j;

    i = 0;
    while (cmds[i])
    {
        j = 0;
        while (cmds[i]->argv[j])
        {
            free(cmds[i]->argv[j]);
            j++;
        }
        // free redirs
        while (cmds[i]->redirs)
        {
            t_redir *tmp = cmds[i]->redirs;
            cmds[i]->redirs = cmds[i]->redirs->next;
            free(tmp->redir_name);
            free(tmp);
        }
        free(cmds[i]->env);
        free(cmds[i]->argv);
        free(cmds[i]->com);
        free(cmds[i]);
        i++;
    }
    free(cmds);
}


t_cmd   **mockup_three_cmds(t_env *env)
{
    t_cmd   **cmds;
    t_cmd   *cmd1;
    t_cmd   *cmd2;
    t_cmd   *cmd3;

// First
    cmd1 = (t_cmd *)malloc(sizeof(t_cmd));
    cmd1->com = ft_strdup("ls");
    cmd1->operat = PIPE;
    cmd1->argv = (char **)malloc(sizeof(char *) * 3);
    cmd1->argv[0] = ft_strdup("ls");
    cmd1->argv[1] = NULL;
    cmd1->argv[2] = NULL;

    t_redir *redir1 = malloc(sizeof(t_redir));
    redir1->redir_sym = NO_REDIR;
    redir1->redir_name = NULL;
    redir1->next = NULL;
    cmd1->redirs = redir1;
    cmd1->context_depth = 0;
    cmd1->env = env;


// Second
    cmd2 = (t_cmd *)malloc(sizeof(t_cmd));
    cmd2->operat = PIPE;
    cmd2->com = ft_strdup("wc");
    cmd2->argv = (char **)malloc(sizeof(char *) * 3);
    cmd2->argv[0] = ft_strdup("wc");
    cmd2->argv[1] = ft_strdup("-c");
    cmd2->argv[2] = NULL;

    t_redir *redir2 = malloc(sizeof(t_redir));
    redir2->redir_sym = NO_REDIR;
    redir2->redir_name = NULL;
    redir2->next = NULL;
    cmd2->redirs = redir2;
    cmd2->context_depth = 0;
    cmd2->env = env;

// Third
    cmd3 = (t_cmd *)malloc(sizeof(t_cmd));
    cmd3->operat = PIPE;
    cmd3->com = ft_strdup("wc");
    cmd3->argv = (char **)malloc(sizeof(char *) * 3);
    cmd3->argv[0] = ft_strdup("wc");
    cmd3->argv[1] = ft_strdup("-c");
    cmd3->argv[2] = NULL;

    t_redir *redir3 = malloc(sizeof(t_redir));
    redir3->redir_sym = NO_REDIR;
    redir3->redir_name = NULL;
    redir3->next = NULL;
    cmd3->redirs = redir3;
    cmd3->env = env;

    cmd3->context_depth = 0;

// Assign to array
    cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 4);
    cmds[0] = cmd1;
    cmds[1] = cmd2;
    cmds[2] = cmd3;
    cmds[3] = NULL;
    return (cmds);
}

t_cmd **mockup_single_cmd(char *envp[])
{
    t_cmd   **cmds;
    t_cmd   *cmd;

    cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 2);
    
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    cmd->com = ft_strdup("cat");
    
    cmd->operat = RUN;

    cmd->argv = (char **)malloc(sizeof(char *) * 3);
    cmd->argv[0] = ft_strdup("cat");
    cmd->argv[1] = NULL;
    cmd->argv[2] = NULL;

    t_env *env = malloc(sizeof(t_env));
    env->envp = envp;
    cmd->env = env;

    // NO_REDIR,
	// RED_INP,
	// RED_OUT,
	// HEAR_DOC,
	// APP_OUT
    t_redir *redir = malloc(sizeof(t_redir));
    // t_redir *redir_2 = malloc(sizeof(t_redir));
    // t_redir *redir_3 = malloc(sizeof(t_redir));
    // t_redir *output_redir = malloc(sizeof(t_redir));
    // t_redir *output_redir2 = malloc(sizeof(t_redir));

    redir->redir_sym = HEAR_DOC;
    redir->redir_name = ft_strdup("end");
    redir->next = NULL;

    // redir_2->redir_sym = RED_INP;
    // redir_2->redir_name = ft_strdup("infile1");
    // redir_2->next = output_redir;

    // redir_3->redir_sym = RED_INP;
    // redir_3->redir_name = ft_strdup("infile2");
    // redir_3->next = output_redir2;
    // // redir_3->next = output_redir;

    // output_redir->redir_sym = RED_OUT;
    // output_redir->redir_name = ft_strdup("outfile");
    // output_redir->next = redir_3;

    // output_redir2->redir_sym = RED_OUT;
    // output_redir2->redir_name = ft_strdup("outfile1");
    // output_redir2->next = NULL;

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

void print_exit_info(int status)
{
    if (WIFEXITED(status))
    {
        ft_putstr_fd("exit status: ", 1);
        ft_putnbr_fd(WEXITSTATUS(status), 1);
        ft_putchar_fd('\n', 1);
    }
    else if (WIFSIGNALED(status))
    {
        ft_putstr_fd("exit signal: ", 1);
        ft_putnbr_fd(WTERMSIG(status), 1);
        ft_putchar_fd('\n', 1);
    }
}

int	main(int argc, char *argv[], const char **envp)
{
	t_cmd	**cmds;

    (void)argc;
	(void)argv;
    t_env *env = init_env(envp);
	cmds = mockup_three_cmds(env);
    // cmds = mockup_single_cmd(envp);
    // cmds = parse_text("pwd", init_env(envp)); // wildcard parsing error: No such file or directory
	execution(cmds);
    free_mockup_cmds(cmds);
	return (0);
}