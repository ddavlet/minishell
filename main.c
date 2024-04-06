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
	return (ft_substr(hostname, 0, ft_strchr(hostname, '.') - hostname));
	// len?
}

char	*create_prompt(t_env *shell_env)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strdup("");
	tmp = find_var(shell_env, "USER");
	prompt = ft_strjoin_free(prompt, tmp);
	free(tmp);
	prompt = ft_strjoin_free(prompt, "@");
	prompt = ft_strjoin_free(prompt, hostname());
	prompt = ft_strjoin(prompt, ":");
	tmp = pwd(shell_env);
	prompt = ft_strjoin_free(prompt, tmp);
	free(tmp);
	prompt = ft_strjoin_free(prompt, "$ ");
	// prompt = "test";
	return (prompt);
}

void	debug_print_to_file(t_cmd **cmds)
{
	int	debug_fd;

	debug_fd = open("debug_log", O_WRONLY | O_CREAT);
	debug_print_cmds(cmds, debug_fd);
	close(debug_fd);
}

void	initialize_shell(t_env *shell_env)
{
	char	*tmp;
	int		i;

	append_envp(shell_env, "SHELL", "minishell");
	tmp = find_var(shell_env, "SHLVL");
	i = ft_atoi(tmp);
	free(tmp);
	tmp = ft_itoa(i + 1);
	append_envp(shell_env, "SHLVL", tmp);
	free(tmp);
	tmp = find_var(shell_env, "PWD");
	add_path(shell_env, tmp);
	free(tmp);
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
	// line = ft_strdup("echo test1 > testfile && (echo test2 || echo test3)");
	// line = ft_strdup("echo test || echo test2");
	free(prompt);
	if (!line)
		terminate_shell(shell_env, EXIT_FAILURE,
			"minishell: failed to read line");
	add_history(line);
}

int	is_subshell(int argc, char **argv)
{
	if (argc == 3 && !ft_strncmp(argv[1], "-n", 3))
		return (1);
	return (0);
}

t_cmd2	*intialize_commands(t_token *tokens, t_env *shell_env)
{
	t_cmd2	*cmds;

	parse_check(tokens, shell_env);
	cmds = parse_command_line(tokens, shell_env);
	free(tokens);
	initialize_variables(cmds, shell_env);
	initialize_wildcards(cmds, shell_env);
	return (cmds);
}

int	main(int argc, char *argv[], const char *envp[])
{
	t_cmd2	*cmds;
	t_token	*tokens;
	t_env	*shell_env;

	shell_env = init_env((const char **)envp);
	initialize_shell(shell_env);
	while (1)
	{
		// signals(getpid());
		if (is_subshell(argc, argv))
			tokens = tokenizer(argv[2]);
		else
			tokens = tokenizer(shell_prompt(shell_env));
		if (!tokens)
			terminate_shell(shell_env, EXIT_FAILURE,
				"minishell: failed to tokenize prompt");
		cmds = initialize_commands(tokens, shell_env);
		// debug_print_cmds(cmds);
		// signals2();
		execution(cmds);
		if (is_subshell(argc, argv))
			terminate_shell(shell_env, EXIT_SUCCESS, NULL);
	}
	return (0);
}
