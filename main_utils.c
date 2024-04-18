/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:33:46 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:33:49 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_subshell(int argc, char **argv)
{
	if (argc == 3 && !ft_strncmp(argv[1], "-n", 3))
		return (1);
	return (0);
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

char	*create_prompt(t_env *shell_env)
{
	char	*prompt;
	char	*host;
	char	*tmp;

	prompt = ft_strdup("");
	tmp = get_variable_value("USER", shell_env);
	prompt = ft_strjoin_free(prompt, tmp);
	free(tmp);
	prompt = ft_strjoin_free(prompt, "@");
	host = hostname();
	prompt = ft_strjoin_free(prompt, host);
	free(host);
	prompt = ft_strjoin_free(prompt, ":");
	tmp = get_relative_pwd(shell_env);
	prompt = ft_strjoin_free(prompt, tmp);
	free(tmp);
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

t_env	*initialize_shell(const char *envp[])
{
	t_env	*shell_env;
	char	*tmp;
	int		i;

	shell_env = init_env((const char **)envp);
	if (!shell_env)
		terminate_shell(NULL, EXIT_FAILURE,
			"minishell: failed to initialize environment");
	append_envp(shell_env, "SHELL", "minishell");
	tmp = get_variable_value("SHLVL", shell_env);
	i = ft_atoi(tmp);
	free(tmp);
	tmp = ft_itoa(i + 1);
	append_envp(shell_env, "SHLVL", tmp);
	free(tmp);
	tmp = get_variable_value("PWD", shell_env);
	add_path(shell_env, tmp);
	free(tmp);
	append_envp(shell_env, "LAST_EXIT_STATUS", "0");
	return (shell_env);
}

char	*shell_prompt(t_env *shell_env)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = create_prompt(shell_env);
	if (!prompt)
		rl_on_new_line();
	line = readline(prompt);
	free(prompt);
	if (!line)
		terminate_shell(shell_env, EXIT_SUCCESS,
			"exit");
	add_history(line);
	return (line);
}
