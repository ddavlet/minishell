#include "execution.h"

char	*get_env_all_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**env_all_path;
	char	*env_path;
	char	*executable_path;
	int		i;

	env_all_path = ft_split(get_env_all_path(envp), ':');
	if (env_all_path == NULL)
		return (NULL);
	i = -1;
	while (env_all_path[++i])
	{
		env_path = ft_strjoin(env_all_path[i], "/");
		executable_path = ft_strjoin(env_path, cmd);
		free(env_path);
		if (access(executable_path, F_OK | X_OK) == 0)
		{
			free_string_arr(env_all_path);
			return (executable_path);
		}
		free(executable_path);
	}
	free_string_arr(env_all_path);
	return (NULL);
}

void	free_string_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	msg_error(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

void	remove_inner_quotes(char **cmd)
{
	int		i;
	char	*untrimmed;

	i = 0;
	while (cmd[i] != NULL)
	{
		untrimmed = cmd[i];
		cmd[i] = ft_strtrim(untrimmed, "\'\"");
		free(untrimmed);
		i++;
	}
}

unsigned long	rand_simple(void)
{
	static unsigned long	lcg_prev = 21512345435143;
	const unsigned long		a = 1103515245;
	const unsigned long		c = 12345;
	const unsigned long		m = 1UL << 31; // 2^31

	lcg_prev = (a * lcg_prev + c) % m;
	return (lcg_prev);
}
