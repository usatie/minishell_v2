#include "minishell.h"

#include <stdio.h>

int	builtin_env(char **argv)
{
	t_item	*cur;

	(void)argv;
	cur = envmap->item_head.next;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->name, cur->value);
		cur = cur->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
