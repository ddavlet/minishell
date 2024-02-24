NAME=debug
SRCS = ./*.c ./io_redirections/*.c ./utils/*.c ../parsing/*.c
INC = -I../parsing/ -I../libft/
LIB = -lreadline
FLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g
all: $(NAME)

$(NAME): $(NAME).c
	make -C ../libft/
	gcc -o $(NAME) $(SRCS)  $(INC) ../libft/libft.a  $(LIB) $(FLAGS)
clean:
	make -C ../libft/ fclean
	rm -f $(NAME)

re: clean all

.PHONY: all clean re