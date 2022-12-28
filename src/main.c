#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>

void	todo(const char *msg) __attribute__((noreturn));

void	todo(const char *msg)
{
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		todo("Interpret command");
		free(line);
	}
	exit(0);
}
