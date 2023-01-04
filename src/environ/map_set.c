#include <stdlib.h>
#include "minishell.h"

#include <string.h>

// name, value 
int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*cur;

	if (name == NULL || !is_identifier(name))
		return (-1);
	cur = map_get(map, name);
	// found
	if (cur)
	{
		free(cur->value);
		if (value == NULL)
			cur->value = NULL;
		else
		{
			cur->value = strdup(value);
			if (cur->value == NULL)
				fatal_error("map_set strdup");
		}
	}
	// not found
	else
	{
		if (value == NULL)
		{
			cur = item_new(strdup(name), NULL, 0);
			if (cur->name == NULL)
				fatal_error("strdup");
		}
		else
		{
			cur = item_new(strdup(name), strdup(value), 0);
			if (cur->name == NULL || cur->value == NULL)
				fatal_error("strdup");
		}
		cur->next = map->item_head.next;
		map->item_head.next = cur;
	}
	return (0);
}

// name, value 
int	map_set_attr(t_map *map, const char *name, const char *value, int attr)
{
	t_item	*cur;

	if (map_set(map, name, value) < 0)
		return (-1);
	cur = map_get(map, name);
	if (cur == NULL)
		assert_error("map_set_attr");
	cur->attributes = attr;
	return (0);
}
