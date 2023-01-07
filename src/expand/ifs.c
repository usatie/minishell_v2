/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:16:44 by susami            #+#    #+#             */
/*   Updated: 2023/01/07 18:18:47 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_default_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_ifs(char c)
{
	char	*ifs;

	ifs = xgetenv("IFS");
	if (ifs == NULL)
		return (is_default_ifs(c));
	if (c == '\0')
		return (false);
	return (ft_strchr(ifs, c) != NULL);
}

bool	consume_default_ifs(char **rest, char *p)
{
	bool	consumed;

	consumed = false;
	while (*p && is_ifs(*p) && is_default_ifs(*p))
	{
		consumed = true;
		p++;
	}
	*rest = p;
	return (consumed);
}

bool	consume_ifs(char **rest, char *line)
{
	if (is_ifs(*line))
	{
		consume_default_ifs(&line, line);
		if (is_ifs(*line))
			line++;
		consume_default_ifs(rest, line);
		return (true);
	}
	*rest = line;
	return (false);
}

void	trim_ifs(char **rest, char *p)
{
	char	*last;

	consume_default_ifs(&p, p);
	*rest = p;
	last = NULL;
	while (*p)
	{
		last = p;
		if (consume_default_ifs(&p, p))
			;
		else
			p++;
	}
	if (last && is_ifs(*last) && is_default_ifs(*last))
		*last = '\0';
}
