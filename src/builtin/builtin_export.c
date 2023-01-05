/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:19 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 18:10:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	print_allenv(void)
{
	t_item	*cur;

	cur = g_ctx.envmap->item_head.next;
	while (cur)
	{
		if (!item_exported(cur))
			;
		else if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->name, cur->value);
		else
			printf("declare -x %s\n", cur->name);
		cur = cur->next;
	}
}

int	builtin_export(char **argv)
{
	size_t	i;
	int		status;

	if (argv[1] == NULL)
	{
		print_allenv();
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(g_ctx.envmap, argv[i], true, ATTR_EXPORT) < 0)
		{
			xperror_invalid_identifier("export", argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
