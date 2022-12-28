NAME = minishell

$(NAME): main.c
	gcc main.c -o $(NAME)
