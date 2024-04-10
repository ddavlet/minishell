#include "main.h"

int	is_subshell(int argc, char **argv)
{
	if (argc == 3 && !ft_strncmp(argv[1], "-n", 3))
		return (1);
	return (0);
}

void    terminate_shell(t_env *shell_env, int exit_status, char *msg)
{
	if (shell_env)
		free_env(shell_env);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
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
	return (ft_substr(hostname, 0, ft_strchr(hostname, '.') - hostname));
}

char	*get_relative_pwd(t_env *env)
{
	char	*pwd;
	char	*home;
	char	*tmp;

	pwd = get_variable_value("PWD", env);
	home = get_variable_value("HOME", env);
	if (ft_strnstr(pwd, home, ft_strlen(home)))
	{
		tmp = ft_substr(pwd, ft_strlen(home), ft_strlen(pwd));
        free(pwd);
		pwd = ft_strjoin("~", tmp);

		free(tmp);
		free(home);
		return (pwd);
	}
	else
	{
		free(home);
		return (pwd);
	}
}
