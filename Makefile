#############
# Variables #
#############

NAME   = minishell
CC     = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
LIBS   = -lreadline
SRCS   = src/main.c
OBJS   = $(SRCS:%.c=%.o)

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
