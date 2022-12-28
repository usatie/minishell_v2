NAME   = minishell
CC     = cc
CFLAGS = -Wall -Wextra -Werror
LIBS   = -lreadline
SRCS   = src/main.c
OBJS   = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./test.sh

.PHONY: all clean fclean re test
