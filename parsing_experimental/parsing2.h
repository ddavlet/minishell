#ifndef PARSING2_H
# define PARSING2_H

# include "../parsing/parsing.h"

typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;
typedef enum e_oper2		t_oper2;
typedef struct e_cmd2		t_cmd2;

typedef enum e_token_type
{
	AND_OR,
	// NAME,
	// ARGUMENT,
	// PARENTHESIS,
	// PIPE,
	// REDIRECTION,
	VARIABLE
}							t_token_type;

typedef enum e_oper2
{
	PIPE,
	AND,
	OR,
	NOTHING
}							t_oper2;

typedef struct s_cmd2
{
	const char				**argv;
	t_redir					*redirectios;
	t_oper2					operation;
	t_cmd2					*next;
}							t_cmd2;

typedef struct s_token
{
	const char				*literal;
	t_token					*next;
}							t_token;

t_token						*tokenizer(const char *line);
t_token						*initialize_token(const char *literal);

t_cmd						*initialize_commands(t_token *tokens);
t_cmd						*parse_line(const char *line);

/*
 *   utils
 */
int							is_between_char(int pos, const char *line, char c);
int							is_between_quotes(const char *line, int pos);
int							is_token(const char *line, const char *token_end);
void						free_tokens(t_token *tokens);

#endif
