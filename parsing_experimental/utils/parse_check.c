#include "../parsing2.h"

void    parse_check(t_token *tokens, t_env *shell_env)
{
	if (!shell_env)
		terminate_parsing(tokens, shell_env, NULL,
			"minishell: failed to parse line: tokens or environment missing");
}