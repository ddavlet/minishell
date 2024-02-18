#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

typedef enum e_oper
{
	RUN,
	PIPE,
	OR,
	AND,
}			t_oper;

typedef enum e_quote
{
	ZERO_Q,
	SIGNLE_Q,
	DOUBLE_Q
}			t_quote;

typedef struct s_com
{
	char			*com;
	bool			legit;
	enum e_oper		operat;
	char			**args;
}					t_com;

typedef struct s_envvar
{
	char			letter;
	bool			exists;
	char			*content;
	struct s_envvar	*child;
	struct s_envvar	*next;
}					t_envvar;

/*Utils*/
char	**pars_split(char const *s);
int		ft_isexeption(char c);
t_quote	ft_isquotation(char c);


/*Terminating functions*/
int		terminate_commands(t_com **commands);
int		terminate_tokens(char **ptr);

/*Error functions*/
void	*error_quot_tockens(char **tokens);


/*Debuging functions*/
void	debug_print_come(t_com **commands);
void	debug_print(t_com *com);
void	debug_print_tokens(char **tokens);

#endif
