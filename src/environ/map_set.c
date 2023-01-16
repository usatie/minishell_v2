/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:29 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 21:51:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "xlib.h"
#include "minishell.h"

// name, value 
static void	item_update(t_item *item, const char *value)
{
	free(item->value);
	if (value == NULL)
		item->value = NULL;
	else
		item->value = xstrdup(value);
}

static void	map_insert(t_map *map, const char *name, const char *value)
{
	t_item	*item;

	if (value == NULL)
		item = item_new(xstrdup(name), NULL, 0);
	else
		item = item_new(xstrdup(name), xstrdup(value), 0);
	item->next = map->item_head.next;
	map->item_head.next = item;
}

int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*item;

	if (name == NULL || !is_identifier(name))
		return (-1);
	item = map_get(map, name);
	if (item)
		item_update(item, value);
	else
		map_insert(map, name, value);
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
