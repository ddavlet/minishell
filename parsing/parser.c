#include "parsing.h"

t_cmd2	*parser(t_token *tokens, t_env *shell_env)
{
	t_cmd2	*cmds;

	parse_check(tokens, shell_env);
	cmds = initialize_commands(tokens, shell_env);
	if (!cmds)
		terminate_parsing(tokens, shell_env, NULL,
			"minishell: failed to parse command line");
	expand_variables(cmds, shell_env);
    process_quotations(cmds, shell_env);

	expand_wildcards(cmds, shell_env);
	return (cmds);
}
