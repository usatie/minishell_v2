#include "../includes/minishell.h"
#include "../includes/libft.h"

void	print_error_and_exit(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(1);
}

void    print_syntax_error(char *unexpected_token)
{
    ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
    ft_putstr_fd(unexpected_token, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
}
 