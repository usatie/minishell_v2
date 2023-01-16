/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:33 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 01:37:40 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "xlib.h"
#include "minishell.h"

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

static void	set_path(char *path, size_t pathsize,
	const char *filename, char **envpath)
{
	size_t	len;
	char	buf[PATH_MAX];
	char	*end;

	ft_bzero(path, pathsize);
	end = ft_strchr(*envpath, ':');
	if (*envpath == end)
		len = ft_strlcpy(path, ".", pathsize);
	else if (end)
	{
		len = ft_strlcpy(buf, *envpath, end - *envpath + 1);
		ft_strlcpy(path, buf, pathsize);
	}
	else
		len = ft_strlcpy(path, *envpath, pathsize);
	len += ft_strlcat(path, "/", pathsize);
	len += ft_strlcat(path, filename, pathsize);
	if (len > pathsize - 1)
		path[0] = '\0';
	if (end == NULL)
		*envpath = NULL;
	else
		*envpath = end + 1;
}

static char	*search_path_mode(const char *filename, int mode)
{
	char	path[PATH_MAX];
	char	*envpath;
	char	*dup;

	envpath = xgetenv("PATH");
	while (envpath && *envpath)
	{
		set_path(path, PATH_MAX, filename, &envpath);
		if (access(path, mode) == 0)
		{
			dup = xstrdup(path);
			return (dup);
		}
	}
	return (NULL);
}
