#############
# Variables #
#############

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

#################
# General rules #
#################

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

##########################
# Platform Compatibility #
##########################

# Linux | Darwin
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	# commands for Linux
endif

ifeq ($(OS),Darwin)
	# commands for macos
	RLDIR = $(shell brew --prefix readline)
	INCLUDES += -I$(RLDIR)/include
	LIBS     += -L$(RLDIR)/lib
endif
