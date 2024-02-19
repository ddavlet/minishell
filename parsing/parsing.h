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
	HEAR_DOC,
	APP_OUT
}			t_red_sym;

typedef struct s_smd
{
	char			*com;
	char			**argv;
	bool			legit;
	enum e_oper		operat;
	struct s_redir	*redirs;
	struct s_env	*env;
}					t_cmd;

typedef struct s_redir
{
	enum e_red_sym	redir_sym;
	char			*redir_name;
	struct s_redir	*next;
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
t_cmd	**parse_text(const char *txt, t_env *root);

/*Tokenization*/
char	**pars_split(char const *s);
char	**merge_quotations(char **tokens);
char	**merge_funct(char **tokens, ssize_t b_q, ssize_t e_q);
char	*find_var(t_env	*root, char *search);


/*Utils*/
int		ft_isexeption(char c);
t_quote	ft_isquotation(char c);
uint32_t	del_pos(const char *txt);

/*Terminating*/
int		terminate_commands(t_cmd **commands);
int		terminate_tokens(char **ptr);
void	terminate_redirs(t_redir *redir_l);


/*Error*/
void	*error_quot_tockens(char **tokens);
/*Debuging*/
void	debug_print_come(t_cmd **commands);
void	debug_print(t_cmd *com);
void	debug_print_tokens(char **tokens);

/**************************************************************/

/*Enviroment function*/
t_env	*init_env(void);
/*Find and set*/
char	*set_envvar(const char *txt, t_env *root);

/*Utils*/
void	add_envvar(t_env *root, char *envvar, const char *content);
void	add_envnode(t_env **list_p, char c, const char *content);
/*Terminating*/
void	terminate_env(t_env *root);

/*Debuging*/
void	debug_print_env(t_env	*root, const char *search);


#endif
