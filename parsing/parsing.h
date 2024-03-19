#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include "./wildcard/wildcard.h"

typedef enum e_oper
{
	RUN,
	PIPE,
	BCKGR,
	OR,
	AND
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

typedef struct s_cmd
{
	char			*com;
	char			**argv;
	enum e_oper		operat;
	int				*scope_stack;
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
ssize_t		ft_commandlen(char **tokens);
char		**add_escape(char **token, const char *esc);
ssize_t		ft_arr_len(char **arr);
ssize_t		arrlen_nosspace(char **arr);
char		**inject_string(char **to_arr, char **from_arr, ssize_t inj_indx);
char		**arrstr_copy(const char **envp);
int			*ft_intarrdup(int *arr);
int			id_gen(int seed);



/*Commands functions*/
t_cmd		**parse_text(const char *txt, t_env *root);
char		**create_argv(char **tokens, ssize_t prev, ssize_t next);
char		**get_wildcard(char **tokens, t_env *root);
void		append_redirnode(t_redir **redir, t_red_sym key,
				const char *value);

/*Tokenization*/
char		**pars_split(char const *s);
char		**pars_merge(char **arr);
char		**merge_quotations(char **tokens);
char		**merge_funct(char **tokens, ssize_t b_q, ssize_t e_q);
char		*find_var(t_env *root, char *search);
void		get_special_cases(char **tokens);

/*Utils*/
t_oper		ft_isexeption(char *txt);
t_quote		ft_isquotation(char c);
t_red_sym	ft_isredir(const char *redir);
uint32_t	del_pos(const char *txt);
t_oper		oper_type(char *txt);
void		trim_quotes(char **tokens);
ssize_t		find_next_cmd(char **tokens, ssize_t i);
char		**parse_delspace(char **tokens);
int			ft_isparenthesis(char *txt);
int			count_brackets(char **arr);


/*Terminating*/
void		*terminate_commands(t_cmd **commands);
void		*terminate_ptr_str(char **ptr);
void		terminate_redirs(t_redir *redir_l);
void		*terminate_cmd(t_cmd *cmd);


/*Error*/
void		*error_quot_tockens(char **tokens);
void		*error_general(void *ptr, const char *str);
void		*error_near_tocken(char *token);
void		*error_syntax(t_cmd *ptr);
void		*undefined_error(char *ptr);



/*Debuging*/
void		debug_print_cmd(t_cmd **commands);
void		debug_print(t_cmd *com);
void		debug_print_array_strings(char **tokens);
void		debug_print_redir(t_redir	*redir);


/**************************************************************/

/*Enviroment function*/
t_env		*init_env(const char **envp);
char		**init_envv(t_env *root);

/*Find and set*/
void		append_envp(t_env *root, char *name, char *content);
void		get_variable(char **tokens, t_env *root);
char		*get_envvar(const char *txt, t_env *root);
int			unset_envvar(t_env *root, const char *to_find);


/*Sytax controllers*/
int			sytax_redir(char *txt);
int			syntax_exeption(char *token);
int			ft_isignored(char *txt);
void		*check_tokens(char **tokens);



/*Utils*/
int			var_exists(char *arg);
char		**append_arr_str(char **arr, char *str);

/*Terminating*/
void		terminate_env(t_env *root);

/*Error*/
void		*error_env_init(void);
void		*error_general(void *ptr, const char *str);

/*Debuging*/
void		debug_print_env(t_env *root, const char *search);

/***************************************************************/

/*Redirection functions*/
t_redir		*init_redir(char **tokens, ssize_t prev, ssize_t next);

#endif
