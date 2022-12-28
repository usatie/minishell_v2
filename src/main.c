#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>

int	ft_system(char *command)
{
	pid_t	pid;
	int		wstatus;
	char 	*argv[] = {"sh", "-c", command, NULL};

	pid = fork();
	if (pid == 0)
	{
		// child
		execve("/bin/sh", argv, NULL);
		exit(1);
	}
	else
	{
		// parent
		waitpid(pid, &wstatus, 0);
	}
	return (wstatus);
}

bool	is_builtin(char *command)
{
	return (strcmp("exit", command) == 0);
}

int	exec_builtin(char *command)
{
	// TODO: cd, echo, pwd, unset, env, export
	if (strcmp("exit", command) == 0)
		exit(0);
	return (0);
}

int	interpret(char *command)
{
	if (is_builtin(command))
		return (exec_builtin(command));
	else
		return (ft_system(command));
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
		status = interpret(line);
		free(line);
	}
	exit(WEXITSTATUS(status));
}
