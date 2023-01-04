#include <stdlib.h>
#include "minishell.h"

#include <string.h>

t_item	*item_new(char *name, char *value, int attributes)
{
	t_item	*item;

	item = calloc(1, sizeof(*item));
	if (item == NULL)
		fatal_error("calloc");
	item->name = name;
	item->value = value;
	item->attributes = attributes;
	return (item);
}

bool	item_exported(t_item *item)
{
	return (item->attributes & ATTR_EXPORT);
}

char	*item_get_string(t_item *item)
{
	size_t	strsize;
	char	*string;

	strsize = strlen(item->name) + 2;
	if (item->value)
		strsize += strlen(item->value);
	string = malloc(strsize);
	if (string == NULL)
		fatal_error("malloc");
	strlcpy(string, item->name, strsize);
	if (item->value)
	{
		strlcat(string, "=", strsize);
		strlcat(string, item->value, strsize);
	}
	return (string);
}
