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

int	main(int argc, char *argv[],const char *envp[])
{
	t_cmd	**cmds;
	char	*line;
	char	*promt;
	t_env	*env;


	(void)argc;
	(void)argv;
	env = init_env((const char **)envp);
	append_envp(env, "SHELL", "minishell");
	line = NULL;
	signals1();
	while (1)
	{
		free(line);
		promt = create_promt(env);
		rl_on_new_line();
		line = readline(promt);
		free(promt);
		if (!line)
			break ;
		if (!line[0])
			continue ;
		add_history(line);
		cmds = parse_text(line, env);
		if (!cmds)
			continue ;
		execution(cmds, cmds[0]->env->envp);
	}
	write(1, "exit\n", 5);
	return (0);
}

void    debug_close_fd(t_fd_state *fd_state)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putstr_fd("DEBUG::closing fd: ", 2);
    ft_putnbr_fd(fd_state->fd, 2);
    ft_putendl_fd("", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_pipe_information(t_pipe *pipe)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd(":pipe information:", 2);
    ft_putstr_fd("DEBUG::write fd: ", 2);
    ft_putnbr_fd(pipe->write->fd, 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::read fd: ", 2);
    ft_putnbr_fd(pipe->read->fd, 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::write is_open: ", 2);
    ft_putnbr_fd(pipe->write->is_open, 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::read is_open: ", 2);
    ft_putnbr_fd(pipe->read->is_open, 2);
    ft_putendl_fd("", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_started(char *msg)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putstr_fd(msg, 2);
    ft_putendl_fd(" started", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_ended(char *msg)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putstr_fd(msg, 2);
    ft_putendl_fd(" ended", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

void    debug_cmd_info(t_executor *exec)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd(":cmd information:", 2);
    ft_putstr_fd("DEBUG::cmd: ", 2);
    ft_putstr_fd(exec->cmds[exec->command_index]->argv[0], 2);
    ft_putendl_fd("", 2);
    ft_putstr_fd("DEBUG::index: ", 2);
    ft_putnbr_fd(exec->command_index, 2);
    ft_putendl_fd("", 2);
    ft_putendl_fd("::::::::::::::::::::::::::::::::::::::::", 2);
}

