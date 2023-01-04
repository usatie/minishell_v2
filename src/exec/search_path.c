#include <limits.h>
#include <unistd.h>
#include "minishell.h"

#include <string.h>

static char	*search_path_mode(const char *filename, int mode);

char	*search_path(const char *filename)
{
	char	*path;

	path = search_path_mode(filename, X_OK);
	if (path)
		return (path);
	path = search_path_mode(filename, F_OK);
	return (path);
}

static char	*search_path_mode(const char *filename, int mode)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = xgetenv("PATH");
	while (*value)
	{
		// /bin:/usr/bin
		//     ^
		//     end
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			strlcpy(path, value, PATH_MAX);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, filename, PATH_MAX);
		if (access(path, mode) == 0)
		{
			char	*dup;

			dup = strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}
