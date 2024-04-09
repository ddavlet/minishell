#include "parsing2.h"

t_cmd2	*initialize_commands(t_token *tokens, t_env *shell_env)
{
	t_cmd2	*cmds;

	parse_check(tokens, shell_env);
	cmds = parse_command_line(tokens, shell_env);
	if (!cmds)
		terminate_parsing(tokens, shell_env, NULL,
			"minishell: failed to parse command line");
	initialize_variables(cmds, shell_env);
    initialize_quotations(cmds, shell_env);
	initialize_wildcards(cmds, shell_env);
	return (cmds);
}
