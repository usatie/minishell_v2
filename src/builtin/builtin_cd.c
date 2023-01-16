/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:55:36 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 01:36:36 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "xlib.h"
#include "minishell.h"

static char	*resolve_pwd(char *oldpwd, char *path);
static void	update_oldpwd(char *pwd);
static int	set_path(char *path, size_t path_size, char *arg);

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

int	builtin_cd(char **argv)
{
	char	*pwd;
	char	path[PATH_MAX];
	char	*newpwd;

	pwd = xgetenv("PWD");
	update_oldpwd(pwd);
	if (set_path(path, PATH_MAX, argv[1]) < 0)
		return (1);
	if (chdir(path) < 0)
	{
		xperror3("cd", path, NULL);
		return (1);
	}
	newpwd = resolve_pwd(pwd, path);
	map_set(g_ctx.envmap, "PWD", newpwd);
	free(newpwd);
	return (0);
}

static char	*resolve_pwd(char *oldpwd, char *path)
{
	char	newpwd[PATH_MAX];
	char	*dup;

	if (*path == '/' || oldpwd == NULL)
		ft_strlcpy(newpwd, "/", PATH_MAX);
	else
		ft_strlcpy(newpwd, oldpwd, PATH_MAX);
	while (*path)
	{
		if (*path == '/')
			path++;
		else if (consume_path(&path, path, "."))
			;
		else if (consume_path(&path, path, ".."))
			delete_last_path_elm(newpwd);
		else
			append_path_elm(newpwd, PATH_MAX, &path, path);
	}
	dup = xstrdup(newpwd);
	return (dup);
}

static void	update_oldpwd(char *pwd)
{
	if (pwd == NULL)
		map_set(g_ctx.envmap, "OLDPWD", "");
	else
		map_set(g_ctx.envmap, "OLDPWD", pwd);
}

static int	set_path(char *path, size_t path_size, char *arg)
{
	char	*home;

	if (arg == NULL)
	{
		home = xgetenv("HOME");
		if (home == NULL)
		{
			xperror2("cd", "HOME not set");
			return (-1);
		}
		ft_strlcpy(path, home, path_size);
	}
	else
		ft_strlcpy(path, arg, path_size);
	return (0);
}
