/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:30:56 by susami            #+#    #+#             */
/*   Updated: 2023/01/07 18:46:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xlib.h"

void	*xcalloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = ft_calloc(count, size);
	if (tmp == NULL)
		fatal_error("xcalloc");
	return (tmp);
}
