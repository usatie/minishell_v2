/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:08:57 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 21:46:10 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	set_name_value(const char *string, char **name, char **value);

int	map_put(t_map *map, const char *string, bool allow_empty_value, int attr)
{
	int		result;
	char	*name;
	char	*value;

	set_name_value(string, &name, &value);
	if (value == NULL && !allow_empty_value)
	{
		free(name);
		return (-1);
	}
	result = map_set_attr(map, name, value, attr);
	free(name);
	free(value);
	return (result);
}

static void	set_name_value(const char *string, char **name, char **value)
{
	char	*name_end;

	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		*name = ft_strdup(string);
		*value = NULL;
		if (*name == NULL)
			fatal_error("ft_strdup");
	}
	else
	{
		*name = ft_strndup(string, name_end - string);
		*value = ft_strdup(name_end + 1);
		if (*name == NULL || *value == NULL)
			fatal_error("ft_strdup");
	}
}
