NAME     = minishell
CC       = cc
RLDIR    = $(shell brew --prefix readline)
INCLUDES = -I include -I$(RLDIR)/include
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
LIBS     = -lreadline -L$(RLDIR)/lib
SRCS     = src/main.c\
           src/error/error.c\
           src/error/error_exit.c\
           src/error/syntax_error.c\
           src/tokenize/token.c\
           src/tokenize/tokenize.c\
           src/tokenize/word.c\
           src/tokenize/name.c\
           src/tokenize/operator.c\
           src/tokenize/blank.c\
           src/tokenize/metacharacter.c\
           src/tokenize/argv.c\
           src/destructor.c\
           src/expand/expand.c\
           src/expand/expand_heredoc.c\
           src/expand/expand_quote_removal.c\
           src/expand/expand_parameter.c\
           src/expand/variable.c\
           src/expand/special_parameter.c\
		   src/parse/parse.c\
		   src/parse/node.c\
		   src/parse/parse_pipeline.c\
		   src/parse/parse_simple_command.c\
		   src/parse/parse_redirection.c\
		   src/redirect/redirect.c\
		   src/redirect/open_redir_file.c\
		   src/redirect/stashfd.c\
		   src/redirect/heredoc.c\
		   src/pipe/pipe.c\
		   src/exec/exec.c\
		   src/exec/search_path.c\
		   src/signal/signal.c\
		   src/signal/signal_handle.c\
		   src/builtin/builtin.c\
		   src/builtin/builtin_exit.c\
		   src/builtin/builtin_export.c\
		   src/builtin/builtin_unset.c\
		   src/builtin/builtin_env.c\
		   src/builtin/builtin_cd.c\
		   src/builtin/builtin_echo.c\
		   src/builtin/builtin_pwd.c\
		   src/environ/map.c\
		   src/environ/map_set.c\
		   src/environ/map_item.c\
		   src/environ/environ.c\

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
