/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:24 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 10:49:22 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

#include <string.h>

t_map	*map_new(void)
{
	t_map	*map;

	map = calloc(1, sizeof(*map));
	if (map == NULL)
		fatal_error("calloc");
	return (map);
}

t_item	*map_get(t_map *map, const char *name)
{
	t_item	*cur;

	if (name == NULL)
		return (NULL);
	cur = map->item_head.next;
	while (cur)
	{
		if (strcmp(cur->name, name) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

int	map_unset(t_map *map, const char *name)
{
	t_item	*cur;
	t_item	*prev;

	if (name == NULL || !is_identifier(name))
		return (-1);
	prev = &map->item_head;
	cur = map->item_head.next;
	while (cur)
	{
		if (strcmp(cur->name, name) == 0)
		{
			prev->next = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = prev->next;
		cur = cur->next;
	}
	return (0);
}

int	map_put(t_map *map, const char *string, bool allow_empty_value, int attr)
{
	int		result;
	char	*name_end;
	char	*name;
	char	*value;

	name_end = strchr(string, '=');
	// value is null
	if (name_end == NULL)
	{
		if (!allow_empty_value)
			return (-1);
		name = strdup(string);
		value = NULL;
		if (name == NULL)
			fatal_error("strdup");
	}
	// value is non null
	else
	{
		name = strndup(string, name_end - string);
		value = strdup(name_end + 1);
		if (name == NULL || value == NULL)
			fatal_error("strdup");
	}
	result = map_set_attr(map, name, value, attr);
	free(name);
	free(value);
	return (result);
}

size_t	map_len(t_map *map, bool count_null_value)
{
	size_t	len;
	t_item	*item;

	len = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value || count_null_value)
			len++;
		item = item->next;
	}
	return (len);
}
