NAME=debug
SRCS = ./*.c ./io_redirections/*.c ./utils/*.c ../parsing/*.c ../parsing/wildcard/*.c
INC = -I../parsing/ -I../libft/
LIB = -lreadline
FLAGS =  -g -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(NAME).c
	make -C ../libft/
	cc -o $(NAME) $(SRCS)  $(INC) ../libft/libft.a  $(LIB) $(FLAGS)
clean:
	make -C ../libft/ fclean
	rm -f $(NAME)

re: clean all

.PHONY: all clean re