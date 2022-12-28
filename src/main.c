#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

int	ft_system(char *command)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == 0)
	{
		// child
		execlp("/bin/sh", "sh", "-c", command, NULL, NULL);
		exit(1);
	}
	else
	{
		// parent
		waitpid(pid, &wstatus, 0);
	}
	return (wstatus);
}

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
		status = ft_system(line);
		free(line);
	}
	exit(WEXITSTATUS(status));
}
