#include "parsing.h"

void	add_cmd(t_cmd2 **ptr_cmds, t_cmd2 *new, t_env *shell_env)
{
	if (!ptr_cmds || !new || !shell_env)
	{
		ft_putendl_fd("failed to add command", STDERR_FILENO);
		return ;
	}
	new->execution->shell_env = shell_env;
	if (*ptr_cmds != NULL)
	{
		new->cmds = *ptr_cmds;
		while ((*ptr_cmds)->next)
			ptr_cmds = &((*ptr_cmds)->next);
		(*ptr_cmds)->next = new;
	}
	else
	{
		new->cmds = new;
		*ptr_cmds = new;
	}
}

t_cmd2	*parse_command_line(t_token *tokens, t_env *shell_env)
{
	t_cmd2 *cmds;
	t_cmd2 *new;
	t_token *start;
	t_token *end;

    parse_check(tokens, shell_env);
	cmds = NULL;
	start = tokens;
	while (start != NULL)
	{
		end = get_final_token(start);
		new = parse_command(start, end);
		if (!new)
			terminate_parsing(tokens, shell_env, cmds,
				"minishell: failed to parse command");
		add_cmd(&cmds, new, shell_env);
		start = end->next;
	}
    free_tokens(tokens);
	return (cmds);
}