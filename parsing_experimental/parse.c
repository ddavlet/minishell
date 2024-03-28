#include "parsing2.h"

t_token	*add_cmd(t_cmd2 **cmds, t_token *tokens)
{
	t_cmd2	*new;
	t_token	*final_token;

	final_token = get_final_token_for_next_cmd(tokens);
	new = get_next_cmd(tokens, final_token);
	if (!new)
		return (NULL);
	if (*cmds == NULL)
		*cmds = new;
	else
	{
		while ((*cmds)->next)
			cmds = (*cmds)->next;
		(*cmds)->next = new;
	}
	return (final_token->next);
}

t_cmd2	*initialize_commands(t_token *tokens)
{
	t_cmd2	*cmds;

	cmds = NULL;
	while (tokens)
		tokens = add_cmd(&cmds, tokens);
	free_tokens(tokens);
	return (cmds);
}

t_cmd2	*parse_line(const char *line)
{
	t_token	*tokens;

	tokens = tokenizer(line);
	return (initialize_commands(tokens));
}