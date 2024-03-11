#include "../libft/libft.h"
#include "execution.h"
#include <stdlib.h>
#include <string.h> // For memcpy
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

int	*mockup_scope_stack(int id_0, int id_1, int id_2)
{
	int	*scope_stack;

	scope_stack = (int *)ft_calloc(4, sizeof(int));
	scope_stack[0] = id_0;
	scope_stack[1] = id_1;
	scope_stack[2] = id_2;
	scope_stack[3] = 0;
	return (scope_stack);
}

t_redir	*mockup_redir(t_red_sym redir_sym, char *redir_name, t_redir *next)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (redir_sym == NO_REDIR)
		return (NULL);
	redir->redir_sym = redir_sym;
	redir->redir_name = redir_name;
	redir->next = next;
	return (redir);
}

t_cmd	*mockup_cmd(char **argv, t_oper operat, int *scope_stack, t_redir *redir, t_env *env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = argv;
	cmd->com = argv[0];
	cmd->env = env;
	cmd->operat = operat;
	cmd->redirs = redir;
	cmd->scope_stack = scope_stack;

	return (cmd);
}

char	**mockup_argv(char *cmd, char *arg1, char *arg2)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * 4);
	argv[0] = ft_strdup(cmd);
	if (arg1)
		argv[1] = ft_strdup(arg1);
	else
		argv[1] = NULL;
	if (arg2)
		argv[2] = ft_strdup(arg2);
	else
		argv[2] = NULL;
	argv[3] = NULL;
	return (argv);
}

t_cmd	**mockup_empty_cmds(void)
{
	t_cmd	**cmds;

	cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	cmds[0] = NULL;
	return (cmds);
}

t_cmd	**mockup_single_cmd(t_env *env)
{
	t_cmd	**cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 2);
	int	*scope_stack = mockup_scope_stack(1, 0, 0);
	t_redir	*in_redir_0;
	t_redir	*in_redir_1;
	t_redir	*in_redir_2;
	t_redir	*out_redir_0;
	in_redir_0 = mockup_redir(HEAR_DOC, "EOF", in_redir_1);
	in_redir_1 = mockup_redir(RED_INP, "misc/infile_A", in_redir_2);
	in_redir_2 = mockup_redir(RED_INP, "misc/infile_B", out_redir_0);
	out_redir_0 = mockup_redir(RED_OUT, "misc/outfile_A", NULL);
	char	**argv = mockup_argv("cat", "misc/infile_A", NULL);
	t_cmd	*cmd = mockup_cmd(argv, RUN, scope_stack, in_redir_0, env);
	cmds[0] = cmd;
	cmds[1] = NULL;
	return (cmds);
}

t_cmd	**mockup_three_cmds(t_env *env)
{
	t_cmd	**cmds = (t_cmd **)malloc(sizeof(t_cmd *) * 4);
	int	*scope_stack = mockup_scope_stack(1, 0, 0);
	// t_redir	*in_redir_0;
	// t_redir	*out_redir_0;
	// in_redir = mockup_redir(HEAR_DOC, "EOF", NULL);
	// out_redir = mockup_redir(RED_INP, "misc/infile_A", NULL);
	char	**argv_0 = mockup_argv("cat", "misc/infile_A", NULL);
	// char	**argv_1 = mockup_argv("wc", "-c", NULL);
	char	**argv_1 = mockup_argv("cat", NULL, NULL);
	char	**argv_2 = mockup_argv("cat", NULL, NULL);
	t_cmd	*cmd_0 = mockup_cmd(argv_0, PIPE, scope_stack, NULL, env);
	t_cmd	*cmd_1 = mockup_cmd(argv_1, PIPE, scope_stack, NULL, env);
	t_cmd	*cmd_2 = mockup_cmd(argv_2, RUN, scope_stack, NULL, env);
	cmds[0] = cmd_0;
	cmds[1] = cmd_1;
	cmds[2] = cmd_2;
	cmds[3] = NULL;
	return (cmds);
}

t_cmd	**mockup_cmds_with_scope(t_env *env)
{
	t_cmd	**cmds = (t_cmd **)ft_calloc(4, sizeof(t_cmd *));
	t_redir	*in_redir_0;
	t_redir	*in_redir_1;
	t_redir	*in_redir_2;
	t_redir	*out_redir_0;
	in_redir_0 = mockup_redir(HEAR_DOC, "EOF", in_redir_1);
	in_redir_1 = mockup_redir(RED_INP, "misc/infile_A", in_redir_2);
	in_redir_2 = mockup_redir(RED_INP, "misc/infile_B", out_redir_0);
	out_redir_0 = mockup_redir(RED_OUT, "misc/outfile_A", NULL);
	int		*scope_stack_A = mockup_scope_stack(1, 0, 0);
	int		*scope_stack_B = mockup_scope_stack(1, 2, 0);
	int		*scope_stack_C = mockup_scope_stack(1, 3, 0);
	//	{1, 2, 0} AND {1, 3, 0} PIPE {1, 0}
	//	{ (cmd0) AND (cmd1 PIPE cmd2) PIPE cmd3 }
	//	{ (cmd0) AND (cmd1 PIPE cmd2) AND cmd3 }
	char 	**argv_0 = mockup_argv("cat", "misc/infile_A", NULL);
	char 	**argv_1 = mockup_argv("pwd", NULL, NULL);
	char 	**argv_2 = mockup_argv("ls", "misc/infile_B", NULL);
	char 	**argv_3 = mockup_argv("cat", NULL, NULL);
	t_cmd	*cmd_0 = mockup_cmd(argv_0, AND, scope_stack_B, NULL, env);
	t_cmd	*cmd_1 = mockup_cmd(argv_1, PIPE, scope_stack_C, NULL, env);
	t_cmd	*cmd_2 = mockup_cmd(argv_2, PIPE, scope_stack_C, NULL, env);
	t_cmd	*cmd_3 = mockup_cmd(argv_3, RUN, scope_stack_A, NULL, env);
	cmds[0] = cmd_0;
	cmds[1] = cmd_1;
	cmds[2] = cmd_2;
	cmds[3] = cmd_3;
	cmds[4] = NULL;
	return (cmds);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd **cmds;

	(void)argc;
	(void)argv;
	t_env *env = init_env((const char **)envp);
	// cmds = mockup_three_cmds(env);
	cmds = mockup_cmds_with_scope(env);
	// cmds = mockup_single_cmd(env);
	// cmds = parse_text("pwd", init_env(envp));
		// wildcard parsing error: No such file or directory
	execution(cmds);
	free_mockup_cmds(cmds);
	return (0);
}