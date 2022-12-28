NAME = libftprintf.a

LIBFTDIR = ../libft

SRCS_ = ft_printf\
		print_str_char\
		num_to_arr\
		print_num_arr\
		flags

SRCS = $(addsuffix .c, $(SRCS_))
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ../../includes/libft.h
CC = gcc

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	cp ../libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

bonus: all

clean:
	make clean -C $(LIBFTDIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFTDIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus