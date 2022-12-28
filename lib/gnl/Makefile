NAME = get_next_line.a

SRCS = get_next_line.c get_next_line_utils.c
OBJS := $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror
CC = gcc

#--------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ ../libft/ft_strlen.o ../libft/ft_safe_free.o ../libft/ft_strchr.o $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY: clean fclean re all