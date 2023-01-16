/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:38:21 by susami            #+#    #+#             */
/*   Updated: 2023/01/07 18:39:19 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	xdup2(int fildes, int fildes2)
{
	int	fd;

	fd = dup2(fildes, fildes2);
	if (fd < 0)
		fatal_error("xdup2");
	return (fd);
}
