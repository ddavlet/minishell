CC := cc
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
UTL_SOURCE := connected.c execute.c get_path.c utils.c
EXE_SOURCE := and_or.c check_exit_value.c execute_builtin.c execution.c pipe.c reverse_pars.c set_io_streams.c \
				$(addprefix $(IO_SRC_DIR), $(IO_SOURCE)) $(addprefix $(UTL_SRC_DIR), $(UTL_SOURCE))
EXE_SRCS = $(addprefix $(EXE_SRC_DIR), $(EXE_SOURCE))
WC_SOURCE := init_utils.c terminating.c wildcard.c
PAR_SOURCE := cmd_utils.c env_utils.c env_utils2.c errors.c errors2.c general_utils.c general_utils2.c pars_utils.c \
				pars_utils2.c pars_utils3.c parsing.c redir_utils.c speccase_utils.c syntax_utils.c terminating.c \
				utils_initenv.c utils_merge.c utils_split.c utils_unsetenvvar.c utils_wildcard.c $(addprefix $(WC_SRC_DIR), $(WC_SOURCE))
PAR_SRCS := $(addprefix $(PAR_SRC_DIR), $(PAR_SOURCE))
BUL_SOURCE := *.C
BUL_SRCS := $(addprefix $(BUL_SRC_DIR), $(BUL_SOURCE))
MAIN := main.c
INC := -Iparsing/ -Ilibft/ -Iexecution/
LIB_DIR := libft/
LIB := -lft -lreadline
FLAGS := -g -Wall -Wextra -Werror
OBJ = $(EXE_SRCS:.c=.o) $(PAR_SRCS:.c=.o) $(MAIN:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(FLAGS) $(INC) -L$(LIB_DIR) $(LIB) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(LIB) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C libft/ fclean


fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re
