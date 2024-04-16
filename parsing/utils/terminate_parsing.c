#include "../parsing.h"

int	terminate_parsing(t_token *tokens, t_env *shell_env, t_cmd2 *cmds,
		char *msg)
{
	// if (shell_env)
	// 	free_env(shell_env);
	free_cmds(cmds);
	free_tokens(tokens);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	append_envp(shell_env, "LAST_EXIT_STATUS", "2");
	return (EXIT_FAILURE);
}
