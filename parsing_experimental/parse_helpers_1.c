#include "parsing2.h"

t_token	*get_final_token_for_next_cmd(t_token *token)
{
    while (token)
    {
        if (is_logic_token(token) || is_pipe_token(token))
            return (token);
        token = token->next;
    }
    return (token);
}

t_cmd2	*get_next_cmd(t_token *tokens, t_token *last)
{
}