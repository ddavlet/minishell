#ifndef PARSING2_H
# define PARSING2_H

# include "../parsing/parsing.h"

typedef struct s_token	t_token;
typedef struct s_cmd2	t_cmd2;
typedef enum e_oper2	t_oper2;

typedef enum e_oper2
{
	PIPE_,
	AND_,
	OR_,
	NOTHING
}						t_oper2;

typedef struct s_cmd2
{
	const char			**argv;
	t_redir				*redirections;
	t_oper2				operation;
	t_cmd2				*next;
}						t_cmd2;

typedef struct s_token
{
	const char			*literal;
	t_token				*next;
}						t_token;

t_token					*tokenizer(const char *line);
t_token					*initialize_token(const char *literal);
void					add_token(t_token **tokens, t_token *new);
t_token					*get_token(const char *line);
t_redir					*parse_redirections(t_token *start, t_token *end);
t_cmd2					*parse_command(t_token *start, t_token *end);
const char				**parse_argv(t_token *start, t_token *end);
t_oper2					parse_operation(t_token *end);
t_cmd2					*parse_command_line(const char *line);
t_cmd2					*parse_command(t_token *start, t_token *end);
t_cmd2					*initialize_command(void);

/*
 *   utils
 */
const char				*merge_quotations_(const char *literal);
int						is_argv_token(t_token *token);
int						is_token(int pos, const char *line);
int						is_pipe_token(t_token *token);
int						is_logic_token(t_token *token);
int						is_redirection_token(t_token *token);
int						is_between_char(int pos, const char *line, char c);
int						is_between_quotes(int pos, const char *line);
void					free_tokens(t_token *tokens);
void					terminate_parsing(const char *line, t_cmd2 *cmds,
							t_token *tokens, char *msg);
t_token					*get_final_token(t_token *token);
void					free_tokens(t_token *tokens);
void					free_redirections(t_redir *redirs);
void					free_argv(char **argv);
void					free_cmds(t_cmd2 *cmds);

#endif
