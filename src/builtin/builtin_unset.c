/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:21 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 18:10:53 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_unset(g_ctx.envmap, argv[i]) < 0)
		{
			xperror_invalid_identifier("unset", argv[i]);
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}
