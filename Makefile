NAME = minishell

INCLUDES = -I ./includes

LIBFTPRINTFDIR = ./lib/printf
GNLDIR = ./lib/gnl

FT_PRINTF = ./lib/printf/libftprintf.a
GNL = ./lib/gnl/get_next_line.a 

LIBS = -lreadline -L$(PRINTFDIR) -lftprintf

$(NAME): mandatory/main.c
	make -C $(LIBFTPRINTFDIR)
	make -C $(GNLDIR)
	gcc $(INCLUDES) mandatory/main.c -o $(NAME) $(FT_PRINTF) $(GNL) $(LIBS)