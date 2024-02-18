#include "execution.h"

int	count_cmds(t_com **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}
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
