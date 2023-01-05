/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:30 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 22:13:55 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"
#include "minishell.h"

#define ERROR_PREFIX "minishell: "

void	perror_prefix(void)
{
	ft_dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	xperror2(const char *s1, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		perror(NULL);
}

void	xperror3(const char *s1, const char *s2, const char *err_msg)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s1);
	ft_dprintf(STDERR_FILENO, "%s: ", s2);
	if (err_msg)
		ft_dprintf(STDERR_FILENO, "%s\n", err_msg);
	else
		perror(NULL);
}

void	xperror_invalid_identifier(const char *s, const char *identifier)
{
	perror_prefix();
	ft_dprintf(STDERR_FILENO, "%s: ", s);
	ft_dprintf(STDERR_FILENO, "`%s': ", identifier);
	ft_dprintf(STDERR_FILENO, "not a valid identifier\n");
}
