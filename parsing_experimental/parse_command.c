#include "parsing2.h"

t_cmd2	*initialize_command(void)
{
	t_cmd2	*cmd;

	cmd = (t_cmd2 *)ft_calloc(1, sizeof(t_cmd2));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->next = NULL;
	cmd->operation = NOTHING;
	cmd->redirections = NULL;
	return (cmd);
}

t_cmd2	*parse_command(t_token *start, t_token *end)
{
	t_cmd2	*cmd;
	t_token	*token;

	cmd = initialize_command();
    if (!cmd)
        return (NULL);
	cmd->redirections = parse_redirections(start, end);
	cmd->argv = parse_argv(start, end);
	cmd->operation = parse_operation(end);
	return (cmd);
}
