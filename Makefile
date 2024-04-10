CC := cc -fsanitize=address
NAME := minishell
RM := rm -f
EXE_SRC_DIR := execution/
PAR2_SRC_DIR := parsing/
PAR_SRC_DIR := parsing/
BUL_SRC_DIR := builtin/
IO_SRC_DIR := io_redirections/
UTL_SRC_DIR := utils/
WC_SRC_DIR := wildcard/
IO_SOURCE := find_last_input_redir.c find_last_output_redir.c handle_append.c handle_here_document.c handle_input.c \
				handle_truncate.c
UTL_EXE_SOURCE := utils.c path.c cmd_check.c 
EXE_SOURCE := commands.c exit_codes.c and_or.c execute_cmd.c execute_builtin.c execution.c pipes.c set_input_output.c \
				$(addprefix $(IO_SRC_DIR), $(IO_SOURCE)) $(addprefix $(UTL_SRC_DIR), $(UTL_EXE_SOURCE))
EXE_SRCS = $(addprefix $(EXE_SRC_DIR), $(EXE_SOURCE))
WC_SOURCE := init_utils.c terminating.c wildcard.c
UTL_PAR2_SOURCE := is_argv_token.c is_logic_token.c is_pipe_token.c is_redirection_token.c is_token.c \
					free_argv.c free_cmds.c free_redirections.c free_tokens.c free_env.c free_ptr_str.c \
					terminate_parsing.c parse_check.c argv_contains_variables.c speccase_utils.c env_utils2.c \
					replace_argv.c argv_contains_wildcards.c close_fd.c argv_contains_quotations.c \
					env_utils.c utils_unsetenvvar.c utils_wildcard.c utils_initenv.c merge_quotations_.c \
					get_final_token.c 
PAR2_SOURCE := parse_argv.c parse_command.c parse_operation.c parse_redirection.c tokenizer.c \
				initialize_commands.c initialize_variables.c parse_command_line.c initialize_wildcards.c \
				initialize_quotations.c \
				$(addprefix $(UTL_SRC_DIR), $(UTL_PAR2_SOURCE)) $(addprefix $(WC_SRC_DIR), $(WC_SOURCE))
# PAR_SOURCE := cmd_utils.c general_utils.c general_utils2.c pars_utils.c \
# 				pars_utils2.c pars_utils3.c parsing.c redir_utils.c syntax_utils.c terminating.c \
# 				utils_merge.c utils_split.c reparsing.c scope.c \
# 				debug.c $(addprefix $(WC_SRC_DIR), $(WC_SOURCE))
PAR2_SRCS := $(addprefix $(PAR2_SRC_DIR), $(PAR2_SOURCE))
# PAR_SRCS := $(addprefix $(PAR_SRC_DIR), $(PAR_SOURCE))
BUL_SOURCE := builtin_utils.c cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUL_SRCS := $(addprefix $(BUL_SRC_DIR), $(BUL_SOURCE))
MAIN := main.c ./signal_handling/signals.c
INC := -Iparsing/ -Ilibft/ -Iexecution/ -Ibuiltin/ -I/opt/homebrew/Cellar/readline/8.2.10/include -I/usr/local/opt/readline/include
LIB_DIR := libft
LIBFT := $(LIB_DIR)libft.a
LIB := -L libft -lft  -L /opt/homebrew/Cellar/readline/8.2.10/lib -lreadline -L/usr/local/opt/readline/lib
FLAGS := -g -Wall -Wextra -Werror
OBJ = $(EXE_SRCS:.c=.o)  $(PAR2_SRCS:.c=.o) $(BUL_SRCS:.c=.o) $(MAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIB_DIR)
%.o: %.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIB_DIR) fclean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re
