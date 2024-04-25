CC := cc
FLAGS := -g -Wall -Wextra -Werror
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
UTL_EXE_SOURCE := utils.c path.c cmd_check.c is_piped.c close_pipe.c close_redir.c terminate_shell.c
EXE_SOURCE := commands.c exit_codes.c and_or.c execute_cmd.c execute_builtin.c execution.c pipes.c set_input_output.c \
				$(addprefix $(IO_SRC_DIR), $(IO_SOURCE)) $(addprefix $(UTL_SRC_DIR), $(UTL_EXE_SOURCE))
EXE_SRCS = $(addprefix $(EXE_SRC_DIR), $(EXE_SOURCE))
WC_SOURCE := init_utils.c terminating.c wildcard.c
UTL_PAR2_SOURCE := is_argv_token.c is_logic_token.c is_pipe_token.c is_redirection_token.c is_token.c \
					free_argv.c free_cmds.c free_redirections.c free_tokens.c free_env.c free_ptr_str.c \
					terminate_parsing.c parse_check.c argv_contains_variables.c speccase_utils.c env_utils2.c \
					replace_argv.c argv_contains_wildcards.c close_fd.c argv_contains_quotations.c \
					env_utils.c utils_unsetenvvar.c utils_wildcard.c utils_initenv.c merge_quotations.c \
					get_final_token.c replace_sequence.c free_array_3d.c is_operation_token.c error_messages.c
PAR2_SOURCE := parse_argv.c parse_nested_argv.c parse_command.c parse_operation.c parse_redirection.c tokenizer.c \
				parser.c expand_variables.c initialize_commands.c expand_wildcards.c \
				process_quotations.c \
				$(addprefix $(UTL_SRC_DIR), $(UTL_PAR2_SOURCE)) $(addprefix $(WC_SRC_DIR), $(WC_SOURCE))
PAR2_SRCS := $(addprefix $(PAR2_SRC_DIR), $(PAR2_SOURCE))
BUL_SOURCE := builtin_utils.c cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUL_SRCS := $(addprefix $(BUL_SRC_DIR), $(BUL_SOURCE))
OBJ_DIR := obj/
MAIN := main.c ./signal_handling/signals.c ./signal_handling/signal_handlers.c main_utils.c
INC := -Iparsing/ -Ilibft/ -Iexecution/ -Ibuiltin/ -I/opt/homebrew/Cellar/readline/8.2.10/include -I/usr/local/opt/readline/include -I/usr/include/readline -I/usr/include
LIB_DIR := libft/
LIBFT := $(LIB_DIR)libft.a
LIBFT_SRC := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putunsnbr_fd.c ft_putnbr_hex_fd.c ft_printf.c ft_get_next_line.c ft_atoi_binar.c ft_strjoinfree.c \
		ft_chararr_len.c ft_chararr_append.c ft_chararr_dup.c ft_intarrdup.c ft_free_ptr.c
LIBFT_SOURCE := $(addprefix $(LIB_DIR), $(LIBFT_SRC))
LIBFT_OBJ = $(LIBFT_SOURCE:.c=.o)
LIB := -L libft -lft  -L /opt/homebrew/Cellar/readline/8.2.10/lib -lreadline -L/usr/local/opt/readline/lib -L/usr/include/readline
OBJ = $(EXE_SRCS:.c=.o)  $(PAR2_SRCS:.c=.o) $(BUL_SRCS:.c=.o) $(MAIN:.c=.o)
OBJ := $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)

$(LIBFT) : $(LIBFT_OBJ)
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) fclean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re
