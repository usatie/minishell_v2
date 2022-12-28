NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LIBS  = -lreadline

all: $(NAME)

$(NAME): src/main.c
	gcc $(CFLAGS) $(LIBS) src/main.c -o $(NAME)

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./test.sh

.PHONY: all clean fclean re test
