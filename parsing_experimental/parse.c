#include "parsing2.h"

void	add_cmd(t_cmd2 **cmds_ptr, t_cmd2 *new)
{
	if (!cmds_ptr || !new)
	{
		ft_putendl_fd("failed to add command", STDERR_FILENO);
		return ;
	}
	if (*cmds_ptr != NULL)
	{
		while ((*cmds_ptr)->next)
			cmds_ptr = &((*cmds_ptr)->next);
		(*cmds_ptr)->next = new;
	}
	else
		*cmds_ptr = new;
}

t_cmd2	*parse_command_line(const char *line)
{
	t_cmd2 *cmds;
	t_cmd2 *new;
	t_token *tokens;
	t_token *end;

	tokens = tokenizer(line);
	cmds = NULL;
	while (tokens)
	{
		end = get_final_token(tokens);
		new = parse_command(tokens, end);
		if (!new)
			terminate_parsing(line, cmds, tokens, "failed to parse command");
		add_cmd(&cmds, new);
		tokens = end->next;
	}
	free_tokens(tokens);
	free((char *)line);
	return (cmds);
}