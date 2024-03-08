#include "../libft/libft.h"
#include "execution.h"
#include <stdlib.h>
#include <string.h> // For memcpy
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	free_mockup_cmds(t_cmd **cmds)
{
	int		i;
	int		j;
	t_redir	*tmp;

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
			tmp = cmds[i]->redirs;
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

t_cmd	**mockup_three_cmds(t_env *env)
{
	t_cmd	**cmds;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	t_cmd	*cmd3;
	t_redir	*redir1;
	t_redir	*redir2;
	t_redir	*redir3;
	int		scope_stack[] = {1, 0};
	cmd1 = (t_cmd *)malloc(sizeof(t_cmd));
	cmd1->argv = (char **)malloc(sizeof(char *) * 3);
    cmd1->scope_stack = (int *)(ft_calloc(3, sizeof(int)));
	redir1 = malloc(sizeof(t_redir));
	cmd2 = (t_cmd *)malloc(sizeof(t_cmd));
	cmd2->argv = (char **)malloc(sizeof(char *) * 3);
    cmd2->scope_stack = (int *)(ft_calloc(3, sizeof(int)));
	redir2 = malloc(sizeof(t_redir));
	cmd3 = (t_cmd *)malloc(sizeof(t_cmd));
    cmd3->scope_stack = (int *)(ft_calloc(3, sizeof(int)));
	cmd3->argv = (char **)malloc(sizeof(char *) * 3);
	redir3 = malloc(sizeof(t_redir));

	redir1->redir_sym = NO_REDIR; //RED_INP;
	redir1->redir_name = "misc/infile_A";
	redir1->next = NULL;
	redir2->redir_sym = NO_REDIR;
	redir2->redir_name = NULL;
	redir2->next = NULL;
	redir3->redir_sym = NO_REDIR;
	redir3->redir_name = NULL;
	redir3->next = NULL;
	// First
	cmd1->com = ft_strdup("cat");
	cmd1->argv[0] = ft_strdup("cat");
	cmd1->argv[1] = ft_strdup("misc/infile_A");
	cmd1->argv[2] = NULL;
	cmd1->operat = PIPE;
	cmd1->redirs = NULL;//redir1;
	cmd1->env = env;
	memcpy(cmd1->scope_stack, scope_stack, 3);

	// Second
	cmd2->operat = PIPE;
	cmd2->com = ft_strdup("wc");
	cmd2->argv[0] = ft_strdup("wc");
	cmd2->argv[1] = ft_strdup("-c");
	cmd2->argv[2] = NULL;
	cmd2->redirs = NULL;//redir2;
	cmd2->env = env;
	memcpy(cmd2->scope_stack, scope_stack, 3);

	// Third
	cmd3->operat = RUN;
	cmd3->com = ft_strdup("wc");
	cmd3->argv[0] = ft_strdup("wc");
	cmd3->argv[1] = ft_strdup("-c");
	cmd3->argv[2] = NULL;
	cmd3->redirs = redir3;
	cmd3->env = env;
    memcpy(cmd3->scope_stack, scope_stack, 3);
	
    // Assign to array
	cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 4);
	cmds[0] = cmd1;
	cmds[1] = cmd2;
	cmds[2] = NULL; //cmd3;
	cmds[3] = NULL;
	return (cmds);
}

t_cmd	**mockup_single_cmd(char *envp[])
{
	t_cmd	**cmds;
	t_cmd	*cmd;
	t_env	*env;
	t_redir	*redir;

	cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 2);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->com = ft_strdup("cat");
	cmd->operat = RUN;
	cmd->argv = (char **)malloc(sizeof(char *) * 3);
	cmd->argv[0] = ft_strdup("cat");
	cmd->argv[1] = NULL;
	cmd->argv[2] = NULL;
	env = malloc(sizeof(t_env));
	env->envp = envp;
	cmd->env = env;
	// NO_REDIR,
	// RED_INP,
	// RED_OUT,
	// HEAR_DOC,
	// APP_OUT
	redir = malloc(sizeof(t_redir));
	// t_redir *redir_2 = malloc(sizeof(t_redir));
	// t_redir *redir_3 = malloc(sizeof(t_redir));
	// t_redir *handle_output_redirection = malloc(sizeof(t_redir));
	// t_redir *output_redir2 = malloc(sizeof(t_redir));
	redir->redir_sym = HEAR_DOC;
	redir->redir_name = ft_strdup("end");
	redir->next = NULL;
	// redir_2->redir_sym = RED_INP;
	// redir_2->redir_name = ft_strdup("infile1");
	// redir_2->next = handle_output_redirection;
	// redir_3->redir_sym = RED_INP;
	// redir_3->redir_name = ft_strdup("infile2");
	// redir_3->next = output_redir2;
	// // redir_3->next = handle_output_redirection;
	// handle_output_redirection->redir_sym = RED_OUT;
	// handle_output_redirection->redir_name = ft_strdup("outfile");
	// handle_output_redirection->next = redir_3;
	// output_redir2->redir_sym = RED_OUT;
	// output_redir2->redir_name = ft_strdup("outfile1");
	// output_redir2->next = NULL;
	cmd->redirs = redir;
	cmds[0] = cmd;
	cmds[1] = NULL;
	return (cmds);
}

t_cmd	**mockup_empty_cmds(void)
{
	t_cmd	**cmds;

	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	cmds[0] = NULL;
	return (cmds);
}

void	print_exit_info(int status)
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
	t_cmd **cmds;

	(void)argc;
	(void)argv;
	t_env *env = init_env(envp);
	cmds = mockup_three_cmds(env);
	// cmds = mockup_single_cmd(envp);
	// cmds = parse_text("pwd", init_env(envp));
		// wildcard parsing error: No such file or directory
	execution(cmds);
	free_mockup_cmds(cmds);
	return (0);
}