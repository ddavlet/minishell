#include "parsing2.h"

int is_logic_token(t_token *token)
{
    if (!token)
        return (0);
    if (token->literal[0])
}








// int	is_redirection(t_token *token)
// {
// 	if (is_input_redir(token) || is_output_redir(token)
// 		|| is_append_redir(token) || is_heredoc_redir(token))
// 		return (1);
// 	return (0);
// }

// int	is_input_redir(t_token *token)
// {

//     if (token->literal[0] == '<')
//     {
//         while 
//     }
// }

// int	is_append_redir(t_token *token)
// {
// }

// int	is_output_redir(t_token *token)
// {
// }

// int	is_heredoc_redir(t_token *token)
// {
// }