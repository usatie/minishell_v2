#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	fatal_error(const char *msg) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(1);
}

int	interpret(char *line)
{
	extern char	**environ;
	char		*argv[] = {line, NULL};
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		// child process
		execve(line, argv, environ);
		fatal_error("execve");
	}
	else
	{
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

int	main(void)
{
	int		status;
	char	*line;

	rl_outstream = stderr;
	status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		status = interpret(line);
		free(line);
	}
	exit(status);
}
