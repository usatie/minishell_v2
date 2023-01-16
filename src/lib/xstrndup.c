/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:38:48 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 21:49:33 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

char	*xstrndup(const char *s1, size_t size)
{
	char	*ret;

	ret = ft_strndup(s1, size);
	if (ret == NULL)
		fatal_error("xstrndup");
	return (ret);
}
