#include "../parsing.h"

void	terminate_parsing(t_token *tokens, t_env *shell_env, t_cmd2 *cmds,
		char *msg)
{
	if (shell_env)
		free_env(shell_env);
	free_cmds(cmds);
	free_tokens(tokens);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
