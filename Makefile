NAME     = minishell
CC       = cc
RLDIR    = $(shell brew --prefix readline)
INCLUDES = -I include -I$(RLDIR)/include
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
LIBS     = -lreadline -L$(RLDIR)/lib
SRCS     = src/main.c\
           src/error.c\
           src/tokenize.c\
           src/destructor.c\
           src/expand.c\
		   src/parse.c\
		   src/redirect.c\
		   src/pipe.c\
		   src/exec.c\
		   src/signal.c\
		   src/builtin.c\
		   src/builtin_exit.c\
		   src/builtin_export.c\
		   src/builtin_unset.c\
		   src/builtin_env.c\
		   src/map.c\
		   src/env.c\

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
