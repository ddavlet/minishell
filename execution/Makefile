NAME=execution
SRCS = $(NAME).c ../testing/testing_utils1.c ../parsing/parsing.c ../parsing/utils_pars.c ../parsing/utils_split.c ../libft/libft.a
INC = -I../testing -I../parsing/

all: $(NAME)

$(NAME): $(NAME).c
	gcc -o $(NAME) $(INC) $(SRCS)  -Wall -Wextra -Werror -std=c99 -pedantic

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re