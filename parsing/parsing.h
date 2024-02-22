#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef enum e_oper
{
	RUN,
	PIPE,
	OR,
	AND,
}					t_oper;

typedef enum e_quote
{
	ZERO_Q,
	SIGNLE_Q,
	DOUBLE_Q
}					t_quote;

typedef enum e_red_sym
{
	NO_REDIR,
	RED_INP,
	RED_OUT,
	HEAR_DOC,
	APP_OUT
}					t_red_sym;

typedef struct s_smd
{
	char			*com;
	char			**argv;
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
	char			**envp;
	struct s_env	*child;
	struct s_env	*next;
}					t_env;

/*General utils*/
ssize_t				ft_commandlen(char **tokens);
char				**add_escape(char **token, const char *esc);
ssize_t				ft_arr_len(char **arr);

/*Commands functions*/
t_cmd				**parse_text(const char *txt, t_env *root);
char				**create_argv(char **tokens, ssize_t prev, ssize_t next);

// t_redir	**init_redir(char **tokens, int len);
void				append_redirnode(t_redir **redir, t_red_sym key,
						const char *value);

/*Tokenization*/
char				**pars_split(char const *s);
char				**pars_merge(char **arr);
char				**merge_quotations(char **tokens);
char				**merge_funct(char **tokens, ssize_t b_q, ssize_t e_q);
char				*find_var(t_env *root, char *search);

/*Utils*/
int					ft_isexeption(char c);
t_quote				ft_isquotation(char c);
t_red_sym			ft_isrediraction(const char *redir);
uint32_t			del_pos(const char *txt);
t_oper				oper_type(char *txt);
void				trim_quotes(char **tokens);
ssize_t				find_next_cmd(char **tokens, ssize_t i);
char				**parse_delspace(char **tokens);

/*Terminating*/
void				*terminate_commands(t_cmd **commands);
int					terminate_ptr_str(char **ptr);
void				terminate_redirs(t_redir *redir_l);

/*Error*/
void				*error_quot_tockens(char **tokens);
void				*error_general(void *ptr, const char *str);
void				*error_near_tocken(char *token);

/*Debuging*/
void				debug_print_cmd(t_cmd **commands);
void				debug_print(t_cmd *com);
void				debug_print_array_strings(char **tokens);

/**************************************************************/

/*Enviroment function*/
t_env				*init_env(const char **envp);
/*Find and set*/
void		append_envp(t_env **envs, char *name, char *content);
void		get_variable(char **tokens, t_env *root);


/*Utils*/

/*Terminating*/
void				terminate_env(t_env *root);

/*Error*/
void				*error_env_init(void);
void				*error_general(void *ptr, const char *str);

/*Debuging*/
void				debug_print_env(t_env *root, const char *search);

/***************************************************************/

/*Redirection functions*/
t_redir				*init_redir(char **tokens, ssize_t prev, ssize_t next);

#endif
