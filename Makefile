NAME = minishell

INCLUDES = -I ./includes

$(NAME): mandatory/main.c
	gcc $(INCLUDES) mandatory/main.c -o $(NAME)