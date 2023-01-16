/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:35:47 by susami            #+#    #+#             */
/*   Updated: 2023/01/10 23:29:56 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "minishell.h"

int	xclose(int fd)
{
	if (fd < 0)
		return (-1);
	if (close(fd) < 0)
		fatal_error("xclose");
	return (0);
}
