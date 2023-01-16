/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:23 by susami            #+#    #+#             */
/*   Updated: 2023/01/13 06:19:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "xlib.h"
#include "minishell.h"

static void	envmap_init(t_map *map, char **ep);

char	*xgetenv(const char *name)
{
	t_item	*item;

	item = map_get(g_ctx.envmap, name);
	if (item == NULL)
		return (NULL);
	return (item->value);
}

void	initenv(void)
{
	extern char	**environ;

	g_ctx.envmap = map_new();
	envmap_init(g_ctx.envmap, environ);
}

char	**get_environ(t_map *map)
{
	size_t	i;
	size_t	size;
	t_item	*item;
	char	**environ;

	size = map_len(map, false) + 1;
	environ = xcalloc(size, sizeof(char *));
	i = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value && item_exported(item))
		{
			environ[i] = item_get_string(item);
			i++;
		}
		item = item->next;
	}
	environ[i] = NULL;
	return (environ);
}

static void	envmap_init(t_map *map, char **ep)
{
	char	cwd[PATH_MAX];

	while (*ep)
	{
		map_put(map, *ep, false, ATTR_EXPORT);
		ep++;
	}
	if (map_get(map, "SHLVL") == NULL)
		map_set_attr(map, "SHLVL", "1", ATTR_EXPORT);
	if (map_get(map, "PWD") == NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			xperror3("shell-init", "getcwd", NULL);
		else
			map_set_attr(map, "PWD", cwd, ATTR_EXPORT);
	}
	map_unset(map, "OLDPWD");
	map_set_attr(map, "OLDPWD", NULL, ATTR_EXPORT);
	map_unset(map, "IFS");
	map_set_attr(map, "IFS", " \t\n", 0);
}
