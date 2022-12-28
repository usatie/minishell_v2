NAME = minishell

INCLUDES = -I ./includes

LIBS = -lreadline

$(NAME): mandatory/main.c
	gcc $(INCLUDES) mandatory/main.c -o $(NAME) $(LIBS)