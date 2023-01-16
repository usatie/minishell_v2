/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:30:56 by susami            #+#    #+#             */
/*   Updated: 2023/01/07 18:34:28 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrdup(const char *s1)
{
	char	*tmp;

	tmp = ft_strdup(s1);
	if (tmp == NULL)
		fatal_error("xstrdup");
	return (tmp);
}
