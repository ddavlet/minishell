#ifndef parsing_H
# define parsing_H

# include "../libft/libft.h"
# include "wildcard/wildcard.h"
# include <stdbool.h>
# include <stdlib.h>
# include <dirent.h>

typedef struct s_token		t_token;
typedef struct s_cmd2		t_cmd2;
typedef enum e_oper2		t_oper2;
typedef struct s_pipe		t_pipe;

typedef struct s_fd_state	t_fd_state;
typedef struct s_pipe		t_pipe;

typedef enum e_red_sym
{
	NO_REDIR,
	RED_INP,
	RED_OUT,
	HEAR_DOC,
	APP_OUT
}							t_red_sym;

typedef struct s_redir
{
	enum e_red_sym			redir_sym;
	char					*redir_name;
	struct s_redir			*next;
}							t_redir;

typedef struct s_env
{
	char					letter;
	bool					exists;
	char					*content;
	char					**envp;
	struct s_env			*child;
	struct s_env			*next;
}							t_env;

typedef struct s_pipe
{
	int						*pipe_fd;
	t_fd_state				*read;
	t_fd_state				*write;
}							t_pipe;

typedef struct s_fd_state
{
	int						fd;
	int						is_open;
	t_pipe					*pipe;
}							t_fd_state;

typedef enum e_oper2
{
	PIPE_,
	AND_,
	OR_,
	NONE
}							t_oper2;

typedef struct s_execution
{
	const char				**argv;
	int						exit_status;
	pid_t					pid;
	t_env					*shell_env;
	t_oper2					operation;
	t_pipe					*pipe;
	t_redir					*redirections;
}							t_execution;

typedef struct s_cmd2
{
	t_execution				*execution;
	t_cmd2					*next;
	t_cmd2					*cmds;
}							t_cmd2;

typedef struct s_token
{
	const char				*literal;
	t_token					*next;
}							t_token;

t_token						*tokenizer(const char *line);
t_token						*initialize_token(const char *literal);
void						add_token(t_token **tokens, t_token *new);
t_token						*get_token(const char *line);
int							parse_redirections(t_redir **ptr_redirs,
								t_token *start, t_token *end);
t_cmd2						*parse_command(t_token *start, t_token *end);
int							parse_argv(char ***ptr_argv, t_token *start,
								t_token *end);
int							parse_operation(t_oper2 *ptr_operation,
								t_token *end);
t_cmd2						*initialize_commands(t_token *tokens,
								t_env *shell_env);
t_cmd2						*parse_command(t_token *start, t_token *end);
t_cmd2						*initialize_command(void);
t_execution					*initialize_execution_data(void);
t_cmd2						*parser(t_token *tokens,
								t_env *shell_env);
void						expand_wildcards(t_cmd2 *cmds,
								t_env *shell_env);
void						expand_variables(t_cmd2 *cmds,
								t_env *shell_env);
char						*get_shell_variable(const char *dollar_sign,
								const char *literal, t_env *shell_env);
void						process_quotations(t_cmd2 *cmds,
								t_env *shell_env);

/*
 *   utils
 */
char						*merge_quotations_(const char *literal);
int							is_argv_token(t_token *token);
int							is_token(int pos, const char *line);
int							is_pipe_token(t_token *token);
int							is_logic_operation_token(t_token *token);
int							is_redirection_token(t_token *token);
int							is_between_char(int pos, const char *line, char c);
int							is_between_quotes(int pos, const char *line);
int							is_special_case(const char *literal);
void						free_tokens(t_token *tokens);
void						terminate_parsing(t_token *tokens, t_env *shell_env,
								t_cmd2 *cmds, char *msg);
t_token						*get_final_token(t_token *token);
void						free_tokens(t_token *tokens);
void						free_redirections(t_redir *redirs);
void						free_argv(const char **argv);
void						free_cmds(t_cmd2 *cmds);
void						parse_check(t_token *tokens, t_env *shell_env);
int							argv_contains_variables(const char **argv);
int							argv_contains_wildcards(const char **argv);
char						*get_case(char *literal, t_env *shell_env);
const char					*find_variable(const char *literal);
int							replace_argv(t_cmd2 *cmd, const char **argv_new);
const char					*replace_variables(const char *literal,
								t_env *shell_env);
void						close_fd(t_fd_state *fd_state);
const char					*get_variable_name(const char *dollar_sign);
int							argv_contains_quotations(const char **argv);
int							contains_quotations(const char *literal);
const char  *escape_quotes(const char *literal);

/*Utils*/
char						**append_arr_str(char **arr, char *str);

/*Terminating*/
void						free_env(t_env *shell_env);

/*Error*/
void						*error_env_init(void);

/*Enviroment function*/
t_env						*init_env(const char **envp);
char						**init_envv(t_env *shell_env);

/*Find and set*/
void						append_envp(t_env *shell_env, char *name,
								char *content);
int							unset_envvar(t_env *shell_env, const char *to_find);
void						add_path(t_env *shell_env, char *path);

char						**get_wildcard(char **tokens, t_env *shell_env);

char						**arrstr_copy(const char **envp);

ssize_t						ft_arr_len(char **arr);
char						*get_variable_value(const char *name,
								t_env *shell_env);
void						*free_ptr_str(char **ptr);

#endif
