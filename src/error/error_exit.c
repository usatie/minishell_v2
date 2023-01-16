/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:31 by susami            #+#    #+#             */
/*   Updated: 2023/01/10 23:25:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "minishell.h"

#include <stdio.h>

void	fatal_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	perror(NULL);
	exit(1);
}

void	assert_error(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: %s\n", location, msg);
	exit(status);
}

void	todo(const char *msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}
