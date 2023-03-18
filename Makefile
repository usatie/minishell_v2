NAME     = minishell
CC       = cc
RLDIR    = $(shell brew --prefix readline)
INCLUDES = -I include -I$(RLDIR)/include
CFLAGS   = -Wall -Wextra -Werror $(INCLUDES)
LIBFTDIR = libft
LIBFT    = $(LIBFTDIR)/libft.a
LIBS     = -lreadline -L$(RLDIR)/lib -lft -L$(LIBFTDIR)
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
           src/expand/expand_word_splitting.c\
           src/expand/ifs.c\
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
		   src/builtin/filepath.c\
		   src/environ/map.c\
		   src/environ/map_set.c\
		   src/environ/map_put.c\
		   src/environ/map_item.c\
		   src/environ/environ.c\
		   src/lib/xdup2.c\
		   src/lib/xstrndup.c\
		   src/lib/xcalloc.c\
		   src/lib/xstrdup.c\
		   src/lib/xpipe.c\
		   src/lib/xclose.c\
		   src/lib/xmalloc.c\

OBJS     = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

bonus: all

install:
	brew install readline

test: all
	./test.sh

norm:
	norminette include src libft
	nm -u $(NAME) | grep -v -E "_(readline|rl_clear_history|rl_on_new_line|\
	rl_replace_line|rl_redisplay|add_history|printf|malloc|free|write|\
	access|open|read|close|fork|wait|waitpid|wait3|wait4|signal|\
	sigaction|sigemptyset|sigaddset|kill|exit|getcwd|chdir|stat|lstat|\
	fstat|unlink|execve|dup|dup2|pipe|opendir|readdir|closedir|\
	strerror|perror|isatty|ttyname|ttyslot|ioctl|getenv|tcsetattr|\
	tcgetattr|tgetent|tgetflag|tgetnum|tgetstr|tgoto|tputs)"

.PHONY: all clean fclean re test norm
