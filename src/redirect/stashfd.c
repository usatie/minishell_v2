/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stashfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:50 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 22:00:50 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "xlib.h"
#include "minishell.h"

static bool	is_valid_fd(int fd)
{
	struct stat	st;

	if (fd < 0)
		return (false);
	errno = 0;
	if (fstat(fd, &st) < 0 && errno == EBADF)
		return (false);
	return (true);
}

int	stashfd(int fd)
{
	int	stashfd;

	if (!is_valid_fd(fd))
	{
		errno = EBADF;
		return (-1);
	}
	stashfd = 10;
	while (is_valid_fd(stashfd))
		stashfd++;
	stashfd = xdup2(fd, stashfd);
	xclose(fd);
	return (stashfd);
}
