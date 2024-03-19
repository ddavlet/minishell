NAME=minishell
SRCS = main.c execution/*.c execution/io_redirections/*.c execution/utils/*.c parsing/*.c parsing/wildcard/*.c
INC = -Iparsing/ -Ilibft/ -Iexecution/
LIB = -lreadline
FLAGS = -g -Wall -Wextra -Werror
all: $(NAME)

$(NAME):
	make -C libft/
	cc -o $(NAME) $(SRCS)  $(INC) libft/libft.a  $(LIB) $(FLAGS)
clean:
	make -C libft/ fclean
	rm -f $(NAME)

re: clean all

.PHONY: all clean re