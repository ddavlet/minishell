CC := cc -fsanitize=address
NAME := minishell
RM := rm -f
EXE_SRC_DIR := execution/
PAR_SRC_DIR := parsing/
BUL_SRC_DIR := builtin/
IO_SRC_DIR := io_redirections/
UTL_SRC_DIR := utils/
WC_SRC_DIR := wildcard/
IO_SOURCE := find_last_input_redir.c find_last_output_redir.c handle_append.c handle_here_document.c handle_input.c \
				handle_truncate.c
UTL_SOURCE := utils.c reverse_pars.c cmds_check.c path.c reset_input_output.c
EXE_SOURCE := commands.c exit_codes.c pids.c and_or.c execute_cmd.c execute_builtin.c execution.c pipes.c set_input_output.c \
				$(addprefix $(IO_SRC_DIR), $(IO_SOURCE)) $(addprefix $(UTL_SRC_DIR), $(UTL_SOURCE))
EXE_SRCS = $(addprefix $(EXE_SRC_DIR), $(EXE_SOURCE))
WC_SOURCE := init_utils.c terminating.c wildcard.c
PAR_SOURCE := cmd_utils.c env_utils.c env_utils2.c errors.c errors2.c general_utils.c general_utils2.c pars_utils.c \
				pars_utils2.c pars_utils3.c parsing.c redir_utils.c speccase_utils.c syntax_utils.c terminating.c \
				utils_initenv.c utils_merge.c utils_split.c utils_unsetenvvar.c utils_wildcard.c reparsing.c \
				debug.c $(addprefix $(WC_SRC_DIR), $(WC_SOURCE))
PAR_SRCS := $(addprefix $(PAR_SRC_DIR), $(PAR_SOURCE))
BUL_SOURCE := builtin_utils.c cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUL_SRCS := $(addprefix $(BUL_SRC_DIR), $(BUL_SOURCE))
MAIN := main.c ./signal_handling/signals.c
INC := -Iparsing/ -Ilibft/ -Iexecution/ -Ibuiltin/ -I/opt/homebrew/Cellar/readline/8.2.10/include -I/usr/local/opt/readline/include
LIB_DIR := libft
LIBFT := $(LIB_DIR)libft.a
LIB := -L libft -lft  -L /opt/homebrew/Cellar/readline/8.2.10/lib -lreadline -L/usr/local/opt/readline/lib
FLAGS := -g -Wall -Wextra -Werror
OBJ = $(EXE_SRCS:.c=.o) $(PAR_SRCS:.c=.o) $(BUL_SRCS:.c=.o) $(MAIN:.c=.o)

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
