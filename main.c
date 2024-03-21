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
		pwd = ft_strjoin("\x1b[32m""~", tmp);
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

	promt = ft_strdup("🤫""\x1b[32m");
	tmp = find_var(env, "USER");
	promt = ft_strjoin_free(promt, tmp);
	free(tmp);
	promt = ft_strjoin_free(promt, "\x1b[0m""@");
	promt = ft_strjoin_free(promt, hostname());
	promt = ft_strjoin(promt, ":");
	tmp = pwd(env);
	promt = ft_strjoin_free(promt, tmp);
	free(tmp);
	promt = ft_strjoin_free(promt, "\x1b[0m""$ ");
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
