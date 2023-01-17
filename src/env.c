#include <stdlib.h>
#include "minishell.h"

#include <string.h>

t_map	*envmap;

static void	envmap_init(t_map *map, char **ep);

char	*xgetenv(const char *name)
{
	return (map_get(envmap, name));
}

void	initenv(void)
{
	extern char	**environ;

	envmap = map_new();
	envmap_init(envmap, environ);
}

char	**get_environ(t_map *map)
{
	size_t	i;
	size_t	size;
	t_item	*item;
	char	**environ;

	size = map_len(map, false) + 1;
	environ = calloc(size, sizeof(char *));
	i = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value)
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
	while (*ep)
	{
		map_put(map, *ep, false);
		ep++;
	}
}
