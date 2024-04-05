#include "main.h"

char	*pwd(t_env *env)
{
	char	*pwd;
	char	*home;
	char	*tmp;

	pwd = find_var(env, "PWD");
	home = find_var(env, "HOME");
	if (ft_strnstr(pwd, home, ft_strlen(home)))
	{
		tmp = ft_substr(pwd, ft_strlen(home), ft_strlen(pwd));
		pwd = ft_strjoin("~", tmp);
		free(tmp);
		free(home);
		return (pwd);
	}
	else
	{
		free(home);
		return (ft_strdup(pwd));
	}
}

char	*hostname(void)
{
	int		fd;
	char	hostname[HOSTNAME_LENGTH];

	fd = open(HOSTNAME_FILE, O_RDONLY);
	ft_bzero(hostname, HOSTNAME_LENGTH);
	if (fd < 0)
	{
		perror("Hostname file open error:");
		return (NULL);
	}
	if (read(fd, hostname, sizeof(hostname)) < 0)
	{
		perror("Hostname file read error:");
		return (NULL);
	}
	return (ft_substr(hostname, 0, ft_strchr(hostname, '.') - hostname)); // len?
}

char	*create_promt(t_env *env)
{
	char	*promt;
	char	*tmp;

	promt = ft_strdup("");
	tmp = find_var(env, "USER");
	promt = ft_strjoin_free(promt, tmp);
	free(tmp);
	promt = ft_strjoin_free(promt, "@");
	promt = ft_strjoin_free(promt, hostname());
	promt = ft_strjoin(promt, ":");
	tmp = pwd(env);
	promt = ft_strjoin_free(promt, tmp);
	free(tmp);
	promt = ft_strjoin_free(promt, "$ ");
	// promt = "test";
	return (promt);
}

void    debug_print_to_file(t_cmd **cmds)
{
    int debug_fd = open("debug_log", O_WRONLY | O_CREAT);
    debug_print_cmds(cmds, debug_fd);
    close(debug_fd);
}

void	subshell(char **tokens, t_env *env)
{
	t_cmd	**cmds;

	cmds = init_commands(tokens);
	for (size_t i = 0; cmds[i]; i++)
		cmds[i]->env = env;

    // debug_print_to_file(cmds);
	execution(cmds, cmds[0]->env->envp);
	terminate_commands(cmds);
}

void	envir_setup(t_env *env)
{
	char	*tmp;
	int		i;

	append_envp(env, "SHELL", "minishell");
	tmp = find_var(env, "SHLVL");
	i = ft_atoi(tmp);
	free(tmp);
	tmp = ft_itoa(i + 1);
	append_envp(env, "SHLVL", tmp);
	free(tmp);
	tmp = find_var(env, "PWD");
	add_path(env, tmp);
	free(tmp);
}

int	main(int argc, char *argv[],const char *envp[])
{
	t_cmd2	*cmds;
	char	*line;
	char	*promt;
	t_env	*env;
    t_token *tokens;

	(void)argc;
	env = init_env((const char **)envp);
	envir_setup(env);
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
		subshell(&argv[2], env);
	line = NULL;
	while (1)
	{
		// signals(getpid());
		free(line);
		promt = create_promt(env);
		rl_on_new_line();
		line = readline(promt);
		// line = ft_strdup("echo test1 > testfile && (echo test2 || echo test3)");
		// line = ft_strdup("echo test || echo test2");
		free(promt);
		if (!line)
			break ;
		if (!line[0])
			continue ;
		add_history(line);
        tokens = tokenizer(line);
        free(line);
		cmds = parse_command_line(tokens);
        free_tokens(tokens);
		// debug_print_cmds(cmds);
		// signals2();
		if (!cmds)
			continue ;
		execution(cmds);
		free_cmds(cmds);
	}
	write(1, "exit\n", 5);
	return (0);
}

// void    debug_close_fd(t_fd_state *fd_state)
// {
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
//     ft_putstr_fd("DEBUG::closing fd: ", 2);
//     ft_putnbr_fd(fd_state->fd, 2);
//     ft_putendl_fd("", 2);
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
// }

// void    debug_pipe_information(t_pipe *pipe)
// {
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
//     ft_putendl_fd(":pipe information:", 2);
//     ft_putstr_fd("DEBUG::write fd: ", 2);
//     ft_putnbr_fd(pipe->write->fd, 2);
//     ft_putendl_fd("", 2);
//     ft_putstr_fd("DEBUG::read fd: ", 2);
//     ft_putnbr_fd(pipe->read->fd, 2);
//     ft_putendl_fd("", 2);
//     ft_putstr_fd("DEBUG::write is_open: ", 2);
//     ft_putnbr_fd(pipe->write->is_open, 2);
//     ft_putendl_fd("", 2);
//     ft_putstr_fd("DEBUG::read is_open: ", 2);
//     ft_putnbr_fd(pipe->read->is_open, 2);
//     ft_putendl_fd("", 2);
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
// }

// void    debug_started(char *msg)
// {
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
//     ft_putstr_fd(msg, 2);
//     ft_putendl_fd(" started", 2);
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
// }

// void    debug_ended(char *msg)
// {
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
//     ft_putstr_fd(msg, 2);
//     ft_putendl_fd(" ended", 2);
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
// }

// void    debug_cmd_info(t_executor *exec)
// {
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
//     ft_putendl_fd(":cmd information:", 2);
//     ft_putstr_fd("DEBUG::cmd: ", 2);
//     ft_putstr_fd(exec->cmds[exec->command_index]->argv[0], 2);
//     ft_putendl_fd("", 2);
//     ft_putstr_fd("DEBUG::index: ", 2);
//     ft_putnbr_fd(exec->command_index, 2);
//     ft_putendl_fd("", 2);
//     ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
// }

