#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdint.h>

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

typedef enum e_red_sym
{
	NO_REDIR,
	RED_INP,
	RED_OUT,
	LIM_INP,
	APP_OUT
}			t_red_sym;

typedef struct s_com
{
	char			*com;
	bool			legit;
	enum e_oper		operat;
	char			**args;
}					t_com;

typedef struct s_redir
{
	enum e_red_sym	redir_sym;
	char			*redir_name;
	struct s_red	*next;
}					t_redir;

typedef struct s_env
{
	char			letter;
	bool			exists;
	char			*content;
	struct s_env	*child;
	struct s_env	*next;
}					t_env;

/*Commands functions*/
t_com	**parse_text(char *txt, t_env *root);
/*Utils*/
char	**pars_split(char const *s);
int		ft_isexeption(char c);
t_quote	ft_isquotation(char c);
/*Terminating*/
int		terminate_commands(t_com **commands);
int		terminate_tokens(char **ptr);
/*Error*/
void	*error_quot_tockens(char **tokens);
/*Debuging*/
void	debug_print_come(t_com **commands);
void	debug_print(t_com *com);
void	debug_print_tokens(char **tokens);

/**************************************************************/

/*Enviroment function*/
t_env	*init_env(void);
/*Utils*/
void	add_envvar(t_env *root, char *envvar, const char *content);
void	add_node(t_env **list_p, char c, const char *content);
/*Terminating*/
void	terminate_env(t_env *root);

/*Debuging*/
void	debug_print_env(t_env	*root, const char *search);


#endif
