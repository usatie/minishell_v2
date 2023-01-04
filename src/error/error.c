#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

#define ERROR_PREFIX "minishell: "

void	perror_prefix(void)
{
	dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}

void	builtin_error(const char *func, const char *name, const char *err)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: ", func);
	if (name)
		dprintf(STDERR_FILENO, "`%s': ", name);
	dprintf(STDERR_FILENO, "%s\n", err);
}
