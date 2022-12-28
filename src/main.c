#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		free(line);
	}
}
