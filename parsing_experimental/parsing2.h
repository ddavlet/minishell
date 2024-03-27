#ifndef PARSING2_H
# define PARSING2_H

# include "../parsing/parsing.h"

typedef enum e_token_type
{
	COMMAND,
	LOGIC_OPERATOR,
	PARENTHESIS,
	PIPE,
	QUOTATION,
	REDIRECTION,
	VARIABLE,
	WHITE_SPACE,
    OTHER
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	const char		*literal;
	t_token			*next;
}					t_token;

#endif
