NAME     = minishell
CC       = cc
INCLUDES = -I include
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
LIBS     = -lreadline
SRCS     = src/main.c\
           src/error.c\
           src/tokenize.c\
           src/destructor.c\
           src/expand.c\
		   src/parse.c\
		   src/redirect.c\

OBJS     = $(SRCS:%.c=%.o)

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
