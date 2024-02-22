NAME=execution_debug
SRCS = execution*.c ./io_redirections/*.c ./utils/*.c ../parsing/*.c
INC = -I../parsing/ -I../libft/
LIB = -lreadline

all: $(NAME)

$(NAME): $(NAME).c
	make -C ../libft/
	gcc -o $(NAME) $(SRCS)  $(INC) ../libft/libft.a  -Wall -Wextra -Werror -std=c99 -pedantic

clean:
	make -C ../libft/ fclean
	rm -f $(NAME)

re: clean all

.PHONY: all clean re