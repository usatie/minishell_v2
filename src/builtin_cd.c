#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "minishell.h"

#include <string.h>

/*
cd [-L|-P] [dir]
	  Change the current directory to dir.  The variable HOME is the default
	  dir.  The variable CDPATH defines the search path for the directory
	  containing dir.  Alternative directory names in CDPATH are separated by a
	  colon (:).  A null directory name in CDPATH is the same as the current
	  directory, i.e., ``.''.  If dir begins with a slash (/), then CDPATH is
	  not used. The -P option says to use the physical directory structure
	  instead of following symbolic links (see also the -P option to the set
	  builtin command); the -L option forces symbolic links to be followed.  An
	  argument of - is equivalent to $OLDPWD.  If a non- empty directory name
	  from CDPATH is used, or if - is the first argument, and the directory
	  change is successful, the absolute pathname of the new working directory
	  is written to the standard output.  The return value is true if the
	  directory was successfully changed; false otherwise.
*/
bool	consume_path(char **rest, char *path, char *elm)
{
	size_t	elm_len;

	elm_len = strlen(elm);
	if (strncmp(path, elm, elm_len) == 0)
	{
		if (path[elm_len] == '\0' || path[elm_len] == '/')
		{
			*rest = path + elm_len;
			return (true);
		}
	}
	return (false);
}

void	delete_last_elm(char *path)
{
	char	*start;
	char	*last_slash_ptr;

	start = path;
	last_slash_ptr = NULL;
	while (*path)
	{
		if (*path == '/')
			last_slash_ptr = path;
		path++;
	}
	if (last_slash_ptr != start)
		*last_slash_ptr = '\0';
}

void	append_path_elm(char *dst, char **rest, char *src)
{
	size_t	elm_len;

	elm_len = 0;
	while (src[elm_len] && src[elm_len] != '/')
		elm_len++;
	// TODO: strcat, strncat is unsafe
	if (dst[strlen(dst) - 1] != '/')
		strcat(dst, "/");
	strncat(dst, src, elm_len);
	*rest = src + elm_len;
}

char	*resolve_pwd(char *oldpwd, char *path)
{
	char	newpwd[PATH_MAX];
	char	*dup;

	if (oldpwd == NULL)
		return (NULL);
	if (*path == '/')
		strlcpy(newpwd, "/", PATH_MAX);
	else
		strlcpy(newpwd, oldpwd, PATH_MAX);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume_path(&path, path, "."))
			;
		else if (consume_path(&path, path, ".."))
			delete_last_elm(newpwd);
		else
			append_path_elm(newpwd, &path, path);
	}
	dup = strdup(newpwd);
	if (dup == NULL)
		fatal_error("strdup");
	return (dup);
}

int	builtin_cd(char **argv)
{
	char	*home;
	char	*oldpwd;
	char	path[PATH_MAX];
	char	*newpwd;

	oldpwd = map_get(envmap, "PWD");
	map_set(envmap, "OLDPWD", oldpwd);
	if (argv[1] == NULL)
	{
		home = map_get(envmap, "HOME");
		if (home == NULL)
		{
			builtin_error("cd", NULL, "HOME not set");
			return (1);
		}
		strlcpy(path, home, PATH_MAX);
	}
	else
		strlcpy(path, argv[1], PATH_MAX);
	if (chdir(path) < 0)
	{
		builtin_error("cd", NULL, "chdir");
		return (1);
	}
	newpwd = resolve_pwd(oldpwd, path);
	map_set(envmap, "PWD", newpwd);
	free(newpwd);
	return (0);
}
