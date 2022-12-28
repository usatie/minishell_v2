NAME = minishell
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): src/main.c
	gcc $(CFLAGS) src/main.c -o $(NAME)

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
