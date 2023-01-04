#include "minishell.h"

#include <stdio.h>

int	builtin_env(char **argv)
{
	t_item	*cur;

	(void)argv;
	cur = envmap->item_head.next;
	while (cur)
	{
		if (!item_exported(cur))
			;
		else if (cur->value == NULL)
			;
		else if (cur->value[0] == '\0')
			;
		else
			printf("%s=%s\n", cur->name, cur->value);
		cur = cur->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}
