#include "main.h"

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
		terminate_shell(shell_env, EXIT_FAILURE,
			"minishell: failed to read line");
	add_history(line);
	return (line);
}

int	main(int argc, char *argv[], const char *envp[])
{
	t_cmd2	*cmds;
	t_token	*tokens;
	t_env	*shell_env;

	shell_env = initialize_shell(envp);
	while (1)
	{
		// signals(getpid());
		if (is_subshell(argc, argv))
			tokens = tokenizer(argv[2]);
		else
		{
			const char *prompt = shell_prompt(shell_env);
			tokens = tokenizer(prompt);
			free((char *)prompt);
		}
		cmds = parser(tokens, shell_env);
		// signals2();
		execution(cmds);
		if (is_subshell(argc, argv))
			terminate_shell(shell_env, EXIT_SUCCESS, NULL);
	}
	return (0);
}
