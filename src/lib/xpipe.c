/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:24:47 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 01:25:25 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "xlib.h"

int	xpipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret < 0)
		fatal_error("xpipe");
	return (ret);
}
