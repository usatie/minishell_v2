#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int	main(void)
{
	int		status;
	char	*line;

	status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		status = system(line);
		free(line);
	}
	exit(WEXITSTATUS(status));
}
